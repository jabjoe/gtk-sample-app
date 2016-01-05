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

### GSettings schemas with standalone Windows applications 

In a standard install .xml schemas files are copied in the system at share/glib-2.0/
 and the gschemas.compiled is re-generated on the system with all the other software.

In a standalone build, we do not need all other software schemas, because the gschemas.compiled
file is relative to the exe (at bin/../share/glib-2.0/gschemas.compiled) except for the GTK settings org.gtk.Settings.ColorChooser.gschema.xml and org.gtk.Settings.FileChooser.gschema.xml).

Unfortunatly glib-compile-schemas can only compile entires directory and not a selection of file.

So when building a standalone exe, xml schemas sampleapp.gschema.xml, org.gtk.Settings.ColorChooser.gschema.xml and org.gtk.Settings.FileChooser.gschema.xml are put in a separate directory (share/glib-2.0/schemas/
) to create a gschemas.compiled

### Icons with standalone Windows applications 

SVG icons of the default theme (adwaita) copyed to share/icons/Adwaita/scalable/*
also share/icons/Adwaita/icon-theme.cache and share/icons/Adwaita/index.theme

After several test, it appears that the following files are also required: 
* lib/gdk-pixbuf-2.0/2.10.0/loaders/libpixbufloader-svg.dll
* lib/gdk-pixbuf-2.0/2.10.0/loaders/loaders.cache The first line of this file also needs to be edited to "../lib/gdk-pixbuf-2.0/2.10.0/loaders/libpixbufloader-svg.dll"



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



