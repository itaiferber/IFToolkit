IFToolkit - by Itai Ferber - itaiferber@gmail.com

Introduction
------------

`IFToolkit` is an umbrella library containing useful code that I commonly use in projects. It contains much of the code found in my other GitHub repositories, and encompasses almost all of my work. Information on each of its components can be found in its corresponding GitHub repository page:

  * [`IFSheetController`](http://github.com/itaiferber/IFSheetController/)
  * [`IFToolbarManager`](http://github.com/itaiferber/IFToolbarManager/)
  * `IFPrint` - not its own project, but still useful code. Documentation found in source.

`IFSheetController` uses Mike Ash's [`MAZeroingWeakRef`](https://github.com/mikeash/MAZeroingWeakRef), and includes the files along with a copy of their BSD license. No customization is necessary, just a copy of `MAZeroingWeakRef.h` and `MAZeroingWeakRef.m` will suffice (the files have been edited very slightly to behave differently if Automatic Reference Counting is turned on - read the ARC section for more info).

Automatic Reference Counting
----------------------------

This framework is compatible with Clang's Automatic Reference Counting feature, available in Apple Clang 3.0 (included in Xcode 4.2). If the `__has_feature(objc_arc)` macro expands to 1 in the preprocessor, all `-retain`, `-release`, and `-autorelease` calls will be removed from the file and replaced with equivalent ARC-compatible code. Because ARC allows for the use of the `__weak` specifier, `MAZeroingWeakRef` is not needed for weak references, and since `MAZeroingWeakRef` will not compile under ARC, it has been modified to not compile if ARC is turned on. You may even remove MAZeroingWeakRef completely from the project if you have ARC turned on to slim the project down.

App Store
---------

No code included in `IFToolkit` makes use of private APIs, but special care is to be taken with `MAZeroingWeakRef`. The copy of `MAZeroingWeakRef` included with the sample project has its 'hackery' level set to 0 (it won't trip off any problems with App Store submissions), but if you decide to include your own copy, make sure `COREFOUNDATION_HACKERY_LEVEL` is indeed set to 0.

Source Code
-----------

The project source code is available on GitHub (in fact, you're most likely already viewing it there):

    http://github.com/itaiferber/IFToolkit/

The source code is bundled under an MIT license, so you're pretty much free to do with it as you wish.

More Information
----------------

Additional documentation can be found in the source code, if needed (header files are extensively documented).
Any outstanding questions you might have will be gladly taken at my email address (supplied above).

Enjoy!