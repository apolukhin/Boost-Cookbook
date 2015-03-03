Boost C++ Application Development Cookbook
===================================
This repository contains all the code examples from the **[Boost C++ Application Development Cookbook](http://www.packtpub.com/boost-cplusplus-application-development-cookbook/book)** `(ISBN: 9781849514880)`, [Packt Publishing](http://www.packtpub.com), by Antony Polukhin.

### Content
This repository contatins project files for QtCreator IDE. `BoostBook.pro` - is the main project file.
See config.txt file for setupping platform specific flags.

QtCreator's project files are very simple and it's easy to understand what is required for example
compilation by just opening the '.pro' file with any text editor.

All source code is distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


### Coding style
Some of the C++ coding styles are broken to fit better cookbook educational format:

* Headers are not always included in the beginning of source and header files.

This is done in attempt to show in which header which classes and functions
are defined. Another goal of doing so, is to avoid errors while copying parts
of code to book (it is simpler and safer to copy required peace of code at
once, instead of gathering together headers and code parts all across the project).

* Our own classes are declared in global namespace (instead of separate namespace).

This is done to reduce amount of unrequired text in book.

* Usually no aliases for namespaces used and usually no `using namespace` used.

This is done for your simplicity. You may open any recipe, start it from the
middle of 'How to do it' part and see a working part of code that does not
require searching all around the chapter for an answer 'In what namespace is
this class defined?'.


### Thanks
Thanks to Heather Gopsill from Packt Publishing for giving a permission to make sources publicly available. 

### Testing
[![Build Status](https://travis-ci.org/apolukhin/Boost-Cookbook-4880OS.svg?branch=master)](https://travis-ci.org/apolukhin/Boost-Cookbook-4880OS) [![Coverage Status](https://coveralls.io/repos/apolukhin/Boost-Cookbook-4880OS/badge.svg)](https://coveralls.io/r/apolukhin/Boost-Cookbook-4880OS)

### Notes for book update
* Chapter 10 "Detecting RTTI support" - add Boost.TypeIndex example
* Optional and Variant now understand rvalue references
* Boost will have an unique_ptr in 1.58
* How about describing boost::future?
* Coroutine interface changed in Boost 1.56
* LexicalCast now has a try_lexical_convert method
* Filesystem is accepted into the Standard
* RCU example using atomics?
* add *_pointer_cast examples?
* add a note to the book about source code availability at github
* sync code and book
