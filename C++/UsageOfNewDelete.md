# When to use new/delete

`new`, `delete` and array forms are used to perform dynamic memory management. `new` and `new[]` run constructors on newly allocated objects, while `delete` and `delete[]` run destructors on deallocated objects.

`new`, `delete` and their array counterparts were the most obvious choice to do dynamic memory allocation in C++98/03. Even though they solve type safety problems stemming from `malloc()`, they don't solve another, more serious problem: ownership. As a result, the following problems are introduced:

### Memory leak
The problem lies in obligation of dynamic memory allocation: programmer *must* free it after it is done, otherwise program will have [memory leak](https://en.wikipedia.org/wiki/Memory_leak). There are multiple solutions to deal with this:

 - Standard smart pointers, paired with `std::make_xxx<type>()`
 - Standard Containers
 - Garbage Collection
 - General RAII

If the frequent dynamic memory allocation is needed, programmer should take care of using one of the above to make sure that program won't leak.

### Dangling pointers
Dangling pointers (or any reference to "dead" object) are pointers to object on which destructor was run or the memory is no longer belongs to the program (e.g. someone already `free()`d or `delete`d it). When accessed (dereferenced or made any sort of access to the pointed to object), undefined behavior will be invoked. Some people consider it as "ownership" problem. Indeed, someone has to delete the pointer, but who? In modern C++, there are well established rules of thumb:

 - Use raw pointers (C pointers, e.g. T*) to imply no ownership (it shouldn't be deleted or freed)
 - Use smart pointers to indicate ownership (smart pointer will automatically destroy the object and free the memory on getting out of scope or when requested). [This](http://stackoverflow.com/questions/106508/what-is-a-smart-pointer-and-when-should-i-use-one) answer should give more details.

Smart pointers might have some performance impact, but standard library maintainers are trying their best to make it cost the same as handwritten version.

###Example:

To show that the problems are not so distant, lets consider the following example:

    class data
    {
    	char* text;
        int* stats;
    public:
    	data()
        {
        	text = new char[count];
            try 
            {
            	stats = new int[count];
            } //if stats throws, text will leak
            catch (const std::bad_alloc& e)
            {
            	delete[] text;
                throw; //rethrow it, since it is an error
            }
        }
        ...
        ~data()
        {
        	delete[] text;
            delete[] stats;
        }
    }

The example above clearly shows that most of the time standard containers (like `std::vector<>`) are better suited for memory management than handwritten version, since they have automatic memory management which guarantees no memory leaks even in exceptional situations. 

Also, since there is no copy constructor that would perform deep copy, implicit copy constructor will perform shallow copy, which will make pointers dangling if copied from object will go out of scope earlier than the copied to object.

## Superior solution

C++ also has automatic storage (sometimes referred to as stack), which is the storage used in function scopes. It automatically runs constructors on declared objects and runs destructors if function returns (either normal or exceptional path), and reclaims memory. Thus, automatic storage should be preferred whenever possible. The only reasons to use dynamic memory allocations are when object is too big (usually stack provided by system is small) and when object needs to outlive current function Further reading on SO: [Why should I use a pointer rather than the object itself?](http://stackoverflow.com/questions/22146094/why-should-i-use-a-pointer-rather-than-the-object-itself?rq=1), [Why should C++ programmer minimize use of `new`](http://stackoverflow.com/questions/6500313/why-should-c-programmers-minimize-use-of-new?rq=1).

## Performance

Performance of `new`, `delete` and their array counterparts is usually implementation dependant, thus it is out of scope of the article. Some of the questions from SO cover a bit of performance.


## Summary
Always prefer automatic storage to dynamic allocation. If free store allocation is needed, use dedicated containers or smart pointers. Always nail down ownership semantics. Use raw pointers to indicate no ownership.