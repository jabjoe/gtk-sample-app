# GTK3 Sample app with

* CMake
* GSettings
* Localization
* Glade UI file with common callbacks (quit/about)

##Base CMake usage

Build and install

    cmake . && make && sudo make install

Build and install under MinGW

    cmake -G "MSYS Makefiles" . && make && make install

Create an Windows installer with NSIS

    cmake -DNSIS=ON -G "MSYS Makefiles" . && make package

## Localization

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



