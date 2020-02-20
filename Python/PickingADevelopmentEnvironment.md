# Picking a Development Environment
## Table of contents
1. [Python Environment](#Python Environment)
2. [Static Analysis](#Static Analysis)
    1. [Linters](#Linters)
    2. [Security](#Security)
    3. [Hinters](#Hinters)
    4. [Metrics](#Metrics)
    5. [Typing](#Typing)
    6. [Packaging](#Packaging)
    7. [Wrappers](#Wrappers)
    8. [Conclusion](#Conclusion)
3. [Unit Tests](#Unit Tests)
    1. [Coverage](#Coverage)
4. [Documentation](#Documentation)
5. [Continuous Integration](#Continuous Integration)

## Python Environment

What are my options?

1. Use the system environment.
2. Use [virtualenv][virtualenv].
3. Use [pyvenv][pyvenv] and/or [venv][venv].
4. Use [pyenv][pyenv].
5. Use [Pipenv][pipenv].

Which can I use together?

 - pyenv can be used with virtualenv and has a helper program to do this - [pyenv-virtualenv][pyenv-virtualenv].
 - Pipenv uses virtualenv, and so by using it you're using both.
 - pyenv and Pipenv can be used together too.

Which should I use?

At a bare minimum you should not use the system environment and instead use virualenv.
IDEs like PyCharm can automate the creation of these, and so modern usage is very simple.  
If you're writing an application, rather than a library, then it's [recommended by the PSF][1] to use Pipenv.  
If you don't have to support Windows and need to run different versions of Python then you can use pyenv.
Alternately you can setup [tox][tox], which allows you to run tests on multiple versions of Python automatically.

And so you should use virtualenv, venv or Pipenv.

<sub>[Click here](https://stackoverflow.com/a/41573588) for more information between these.</sub>


  [1]: https://packaging.python.org/guides/tool-recommendations/#application-dependency-management

  [virtualenv]: https://pypi.org/project/virtualenv/
  [pyvenv]: https://docs.python.org/3.5/using/scripts.html
  [venv]: https://docs.python.org/3/library/venv.html
  [pyenv]: https://pypi.org/project/pyenv/
  [pipenv]: https://pypi.org/project/pipenv/
  [pyenv-virtualenv]: https://github.com/pyenv/pyenv-virtualenv

## Static Analysis

You should want some level of static analysis in your development environment and in your continuous integration.
There's quite a wide variety of static analysers, and so you should know what these are and what the differences are.

1. [Linters](#Linters)  
    These go through your code and find potential errors.
    Even within these there are three main types of error that these raise.
    
    - Style Errors  
        These are errors that revolve style guides. Such as PEP 8 compliance.
    - Logical Errors  
        These are potential errors with your code, such as suggesting to use a function rather than a class.

2. [Security](#Security)  
    These look for security problems in your code, such as SQL injection vulnerabilities or publishing secrets.

2. [Hinters](#Hinters)  
    These automatically fix errors in your code, however they are normally limited to Style Errors.

3. [Metrics](#Metrics)  
    These look at your code and analyse the complexity of your code. Notifying you to functions or classes you should refactor.

4. [Typing](#Typing)  
    This analyses type hints in your program to verify if your program is passing valid objects to functions.
    Support for `typing` is relatively new, but lack of static types is one of the biggest criticisms for Python.

5. [Packaging](#Packaging)  
    These perform various types of analysis on your Python packaging and dependencies.

6. [Wrappers](#Wrappers)  
    These are tools that wrap other tools, so that there is one interface to work with.

### Linters

What linters are available?

The most popular are:

 - [PyChecker][pychecker]
 - [pycodestyle][pycodestyle]
 - [pydocstyle][pydocstyle]
 - [Pyflakes][pyflakes]
 - [PyLint][pylint]

Most other:

 - [Bellybutton][bellybutton]
 - [CloneDigger][clonedigger]
 - [Flake8 extensions](https://github.com/DmytroLitvinov/awesome-flake8-extensions)
 - [Frosted][frosted] (pyflakes fork)
 - [GJSLint][gjslint]
 - [Jedi][jedi]
 - [py-find-injection][py-find-injection]
 - [Pydiatra][pydiatra]
 - PyLint extensions
 - [TwistedChecker][twistedchecker]
 - [Vulture][vulture]

Which should I use?

I'd suggest that you install at least one generic linter.
However installing multiple increases the amount of potential errors they find.

 - [Pyflakes][pyflakes]
 - [PyLint][pylint]
 - [Bellybutton][bellybutton]
 - [Frosted][frosted]
 - [Jedi][jedi]
 - [Pydiatra][pydiatra]
 - [TwistedChecker][twistedchecker]

After this you're left with a couple of linters with clear goals, such as code deduplication.
And then there are quite a few extensions to PyLint and Flake8 that you may want.

  [pychecker]: https://pypi.org/project/PyChecker/
  [pycodestyle]: https://pypi.org/project/pycodestyle/
  [pydocstyle]: https://pypi.org/project/pydocstyle/
  [pyflakes]: https://pypi.org/project/pyflakes/
  [pylint]: https://pypi.org/project/pylint/
  [bellybutton]: https://pypi.org/project/bellybutton/
  [clonedigger]: https://pypi.org/project/clonedigger/
  [frosted]: https://pypi.org/project/frosted/
  [gjslint]: https://pypi.org/project/pylama_gjslint/
  [jedi]: https://pypi.org/project/jedi/
  [py-find-injection]: https://pypi.org/project/py-find-injection/
  [pydiatra]: https://pypi.org/project/pydiatra/
  [twistedchecker]: https://pypi.org/project/TwistedChecker/
  [vulture]: https://pypi.org/project/vulture/

### Security

What security tools are available?

 - [Bandit][bandit]
 - [detect-secrets][detect-secrets]
 - [Dodgy][dodgy]
 - [Python-taint][python-taint]

You should install all security linters no matter what the project is.
This is as these catch problems that go against security best practices, and so leave you open for attack.

  [bandit]: https://pypi.org/project/bandit/
  [detect-secrets]: https://pypi.org/project/detect-secrets/
  [dodgy]: https://pypi.org/project/dodgy/
  [python-taint]: https://pypi.org/project/python-taint/

### Hinters

What hinters are available?

 - [autoflake][autoflake]
 - [autopep8][autopep8]
 - [black][black]
 - [eradicate][eradicate]
 - [isort][isort]
 - [yapf][yapf]

  [autoflake]: https://pypi.org/project/autoflake/
  [autopep8]: https://pypi.org/project/autopep8/
  [black]: https://pypi.org/project/black/
  [eradicate]: https://pypi.org/project/eradicate/
  [isort]: https://pypi.org/project/isort/
  [yapf]: https://pypi.org/project/yapf/

### Metrics

What metrics are available?

 - [Mccabe][mccabe]
 - [Radon][radon]

Randon is a superset of Mccabe, runnable only through Flake8.
Unfortunately most wrappers don't support Flake8 and so most don't support Randon.

  [mccabe]: https://pypi.org/project/mccabe/
  [radon]: https://pypi.org/project/radon/

### Typing

What typing inspections are available?

 - [mypy][mypy]
 - [pyre-check][pyre-check]
 - [pyright][pyright]
 - [pytype][pytype]

These all perform the same function, and they're all pretty new. So pick one or two and you should be set.

It should be noted that typeshed requires that the tests run correctly on both mypy and pytype.

<!--
TODO: https://mypy.readthedocs.io/en/latest/existing_code.html#automate-annotation-of-legacy-code
TODO: https://www.python.org/dev/peps/pep-0561/
-->

  [mypy]: https://pypi.org/project/mypy/
  [pyre-check]: https://pypi.org/project/pyre-check/
  [pyright]: https://github.com/Microsoft/pyright
  [pytype]: https://pypi.org/project/pytype/

### Packaging

 - [check-manifest][check-manifest]
 - [dependency-check][dependency-check]
 - [pipenv][pipenv]
 - [pyroma][pyroma]
 - [pyup-django][pyup-django]
 - [requirements-detector][requirements-detector]
 - [safety][safety]

  [check-manifest]: https://pypi.org/project/check-manifest/
  [dependency-check]: https://pypi.org/project/dependency-check/
  [pyroma]: https://pypi.org/project/pyroma/
  [pyup-django]: https://pypi.org/project/pyup-django/
  [requirements-detector]: https://pypi.org/project/requirements-detector/
  [safety]: https://pypi.org/project/safety/

### Wrappers

What wrappers are available?

 - [Flake8][flake8]
 - [Coala][coala]
 - [Prospector][prospector]
 - [PyLama][pylama]

What do they have?

 - [pycodestyle][pycodestyle]
 - [pydocstyle][pydocstyle]
 - [pyflakes][pyflakes]

What are the other overlaps between them? This can be seen in the following diagram. I have removed the packages that they all have in common:

[![][2]][2]

From this it should be apparent that PyLama is almost the same as Flake8 + PyLint or Coala + Mccabe.
We can also see that Prospector + Flake8 wraps everything Coala does minus hinting software.
And so the choice is pretty easy:

Do you want hinting?

 - Yes: [Coala][coala]
 - No: [Prospector][prospector] + [Flake8][flake8]

  [2]: wrapper-diagram.png
  
  [flake8]: https://pypi.org/project/flake8/
  [coala]: https://pypi.org/project/coala/
  [prospector]: https://pypi.org/project/prospector/
  [pylama]: https://pypi.org/project/pylama/

### Conclusion

Do you want builtin hinters?

 - Yes: [Coala][coala]
 - No: [Prospector][prospector] + [Flake8][flake8]

You should also install:

 - [detect-secrets][detect-secrets]
 - [dodgy][dodgy]
 - [python-taint][python-taint]

And any [packaging](#Packaging) tools you want.

It should be noted that a lot of the [linters](#Linters) arn't included in Coala, Prospector or Flake8.

## Unit Tests

<sub>[A more complete list of testing tools](https://wiki.python.org/moin/PythonTestingToolsTaxonomy#Unit_Testing_Tools)</sub>

Which one is best? Unfortunately there's no correct answer to this.

 - Is your program a one-off script?  
    [Doctest][doctest]
 - Otherwise the following are largely used unit test frameworks:
     - [unittest][unittest] (also known as PyUnit)
     - [Nose2][nose2]
     - [pytest][pytest]
     
     It should be noted that pytest can run a subset of unittest, Nose2 and doctest test suites.

And so pytest seems like the best way to run these tests.

  [autotest]: https://pypi.org/project/autotest/
  [avocado]: https://pypi.org/project/avocado-framework/
  [unittest]: https://docs.python.org/3/library/unittest.html
  [unittest2]: https://pypi.org/project/unittest2/
  [testoob]: https://pypi.org/project/testoob/
  [doctest]: https://docs.python.org/3/library/doctest.html
  [nose]: https://pypi.org/project/nose/
  [nose2]: https://pypi.org/project/nose2/
  [pytest]: https://pypi.org/project/pytest/
  [twistedtrial]: https://pypi.org/project/Twisted/
  [should_dsl]: https://pypi.org/project/should_dsl/
  [green]: https://pypi.org/project/green/

  [tox]: https://pypi.org/project/tox/
 
### Coverage

What coverage modules are available?

 - [coverage.py](https://pypi.org/project/coverage/)
 - [pytest-cov](https://pypi.org/project/pytest-cov/)

It should be noted that pytest-cov uses coverage.py. In short use the latter if you use pytest, otherwise the former.

## Documentation

<sub>[A more complete list of documentation tools](https://wiki.python.org/moin/DocumentationTools)</sub>

What are the most common?

 - [Sphinx](https://pypi.org/project/Sphinx/)
 - [Doxygen](http://doxygen.nl/)

Sphinx plays a big part in Python documentation, it's what the Python docs use, and is what [Read the Docs](https://docs.readthedocs.io) uses.

## Continuous Integration

### Test Automation

Since there are a lot of tools that need to run, it helps to use test automation software.

 - [Tox](https://pypi.org/project/tox/)
 - [Nox](https://pypi.org/project/nox/)
 - [Invoke](https://pypi.org/project/invoke/)
 - [Make](https://en.wikipedia.org/wiki/Make_(software)#Derivatives)

Tox is pretty much the de facto standard when you need to test multiple instances of Python.
This makes it really easy to test on Python 2.7 and Python 3.x.

### Continuous Integration Software

<sub>[For an more complete list see here](https://en.wikipedia.org/wiki/Comparison_of_continuous_integration_software).</sub>

 - [Travis CI](https://travis-ci.org/)
 - [Jenkins](https://jenkins.io/)
 - [GitLab](https://about.gitlab.com/product/continuous-integration/)
 - [TFS](https://visualstudio.microsoft.com/tfs/)

If you already have a CI server already, such as GitLab or TFS, then you may want to use that.

Jenkins is great if you want to host your own server.
This is great for private software.

If you're developing open source code Travis CI is free and used by a lot of open source Python projects.
