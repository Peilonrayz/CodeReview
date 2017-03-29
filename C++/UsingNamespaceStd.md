# Why you should stop writing `using namespace std` in most cases?

To answer the question, we first need to have a solid understanding of what they are and how to use them. After discussing that, it should be clear that `using namespace std` in the global scope is erroneous.

## What are C++ namespaces and how to use them?

Primarily it is a name mangling and name resolution control mechanism. At least this is what is observable.

## Code size

It slightly increases code size. Name of the namespace is not so long, and writing `std::` should be affordable. It might make code arguably harder to read, but advantages usually outweight disadvantages.

## Name collision

If you came from C background, you probably are familiar with this. Name collision is an error which is caused by the same names (in case of functions, it is the same signature. In case of template functions, it is the same function signature after substitution and return type. In case of template structs/classes, it is the same arguments passed to template). Name collision makes choosing good names much harder, because you will always need to worry about preventing the name collision by using some macros. In C++, namespaces resolve this issue (actually they diminish it to the point that it is no longer a problem). 

## Overload resolution control

This is one of the reasons when you want to actually import a name from a namespace. Just do it in a very narrow scope and only on very few situations, one of which I will cover next.
I will call it swap expression. So, basically when you write `using namespace std`, names from `std` will get imported into current scope. What will happen is if there is a situation, for example, swap, compiler first will try to find `swap()` function in the current scope. So, if you want to have different behavior of swap, you can write your own in the current scope (or you can import it) and compiler will happily invoke it when you call swap.

    using std::swap;
    swap(first, second);
    
But, if there is no `swap()` function declared in the current scope, it will invoke standard one, `std::swap()`. Isn't this great? Namespaces provide sort of a fallback mechanism which simplifies metaprogramming.

Although it provides an advantage, it is a double edged sword. One can make unqualified call (e.g. with no namespace specifier), and expect a function from namespace `X` to be called, but function from the current namespace will be called if both of them are perfect match. Thus, it is important to keep current scope tight and introduce as less names as possible to not get confused.

# Conclusion

As discussed above, `using namespace std` is almost always not what C++ programmer needs. In some cases `using` statements should be used, but there are too few situations for that, and they generally occur in generic code.