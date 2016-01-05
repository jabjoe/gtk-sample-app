# GTK3 Sample app using

* CMake
* GSettings
* Localization
* Glade UI file with common callbacks (quit/about)

# Build 
## Under Linux

<pre>
--generate Makefile and config.h
$cmake . 
--generate binary
$make
--install files, settings and binaries
#make install
</pre>

## Under Windows 

MSYS2 with MinGW-W64 is the 'official' build method. 

* Get MSYS2 from http://msys2.github.io/
* With MSYS2 shell Install MinGW toolchain (gcc, make) and dependencies (cmake and gtk3) 

pacman -S  mingw-w64-i686-toolchain mingw32/mingw-w64-i686-cmake mingw32/mingw-w64-i686-gtk3

With a MinGW Shell go to the gjitenkai directory and do :

    cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release . && mingw32-make.exe && mingw32-make.exe install

### Create an installer 

* Install NSIS from sourceforge

in a MinGW-W64 shell go to the gjitenkai directory and  do :

    cmake -DCMAKE_BUILD_TYPE=Release -DNSIS=ON . && cpack


# Localization

Scan for translatable text in a Glade file

    xgettext --sort-output --keyword=translatable -o po/sampleapp.pot data/ui.glade

For Example, for French, copy pot file to fr/sampleapp.po

Set Content-type with "Content-Type: text/plain; charset=UTF-8\n"

Create binary file with `msgfmt`

    msgfmt sampleapp.po -o sampleapp.mo

Testing localization

List installed locales with the `locale` command 

    locale -a

Under linux, test by changing the local with

    LANG=fr_FR.utf8 ./bin/sampleapp



