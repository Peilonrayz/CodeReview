# Table of Contents

1. [Manual Execution](#Manual Execution)
    1. [Python Environment](#Python Environment)
    2. [Static Analysis](#Static Analysis)
        1. [Prospector](#Prospector)
        2. [flake8](#flake8)
        3. [Detect Secrets](#Detect Secrets)
    3. [Tests](#Tests)
2. [Automatic Execution](#Automatic Execution)
3. [Continuous Integration](#Continuous Integration)

# Manual Execution

This section explains how to use all the tools individually, which is a prerequisite to setting up and using an automated runner.

## Python Environment

<sub>[Why pipenv](PickingADevelopmentEnvironment.md#Python Environment).</sub>  
Setting up a pipenv environment.

```bash
../ $ mkdir project
../ $ cd project
$ pip install --user pipenv
``` 

**Note**: you may have to add [`site.USER_BASE`][0] to your PATH.

From here you can:

 - Install:
    ```bash
    $ pipenv install ...
    ```
 - Run:
    ```bash
    $ pipenv run python example.py
    ```
 - Enter virtual environment:
    ```bash
    $ pipenv shell
    ```

## Static Analysis

<sub>Why [Prospector + Flake8](PickingADevelopmentEnvironment.md#Wrappers), [detect-secrets](PickingADevelopmentEnvironment.md#Security) and [mypy](PickingADevelopmentEnvironment.md#Typing).</sub>  
First we have to install the programs that we want to use. Since Prospector and Flake8 both use target pinning you may get an error when trying to install. This means that you'll have to use an older version of one of them.

```bash
$ pipenv install --dev prospector[with_everything] flake8 radon detect-secrets
```

### Prospector

To get all the errors use the following.

```bash
$ prospector -s veryhigh -w frosted -w mypy -w pyroma -w vulture
```

Alternately you can setup a [`.prospector.yaml`][6].

```yaml
strictness: veryhigh
doc-warnings: true
test-warnings: true
member-warnings: true

frosted:
  run: true

mypy:
  run: true

pyroma:
  run: true

vulture:
  run: true
```

### Flake8

Flake8 is really easy to use. You can also [configure it through a `setup.cfg` or `tox.ini`][7].

```bash
$ flake8
```

#### Radon

You can [run Radon with flake8][8].

```bash
$ flake8 --radon-max-cc 10
```

Alternately you can use the [`radon` commands][9].

```bash
$ radon cc .
$ radon mi .
$ radon raw .
$ radon hal .
```

### Detect Secrets

If you already have a project with secrets setup you can setup a baseline to ignore these.

```bash
$ detect-secrets scan > .secrets.baseline
```

From this you can run it from the command line.

```bash
detect-secrets scan .
```

**Note**: It's recommended to [set it up as a pre-commit hook][10].

## Tests
### Doctest
#### Install

`doctest` is included in the Python standard library.

#### Usage

If you have doctests in your file all you need to do is run doctest passing the file name to test on.

```bash
$ python -m doctest example.py
```

Where `example.py` can be as simple as:

```python
def fn(n):
    """
    >>> fn(-1)
    Traceback (most recent call last):
        ...
    ValueError: n must be >= 0
    >>> fn(0)
    0
    >>> fn(5)
    15
    """
    if n < 0:
        raise ValueError('n must be >= 0')
    if n <= 10:
        return n
    return n + 10
```

#### Coverage

Make sure you have coverage installed.

```bash
$ pipenv install --dev coverage
```

Use coverage like you would Python

```bash
$ coverage -m doctest example.py
```

### pytest
#### Install

```bash
$ pipenv install --dev pytest
```

#### Usage
#### pytest-cov

# Automatic Execution
## Test Automation

<sub>[Why tox](PickingADevelopmentEnvironment.md#Test Automation).</sub>

Tox helps automate the install and usage of the tools we've manually installed and used above.

Not only does it mean that running all the tools the way you want becomes easy, it also means other people can install and run using one command too.

### Install

Installing is as easy as any other package.
It should be noted that the directory that `--user` flag places the files into sometimes isn't in your path, and so you may have to add it yourself. 

```bash
$ pip install --user tox
```


# Continuous Integration

  [0]: https://docs.python.org/3/library/site.html#site.USER_BASE
  

  [0]: https://prospector.readthedocs.io/en/master/supported_tools.html
  [1]: https://prospector.readthedocs.io/en/master/profiles.html
  [2]: https://www.python.org/dev/peps/pep-0484/
  [3]: https://www.python.org/dev/peps/pep-0526/
  [4]: https://wiki.python.org/moin/PythonTestingToolsTaxonomy#Unit_Testing_Tools
  [5]: https://pypi.org/
  [6]: https://prospector.landscape.io/en/master/profiles.html
  [7]: http://flake8.pycqa.org/en/latest/user/configuration.html
  [8]: https://radon.readthedocs.io/en/latest/flake8.html
  [9]: https://radon.readthedocs.io/en/latest/commandline.html
  [10]: https://github.com/Yelp/detect-secrets#pre-commit-hook