# GTK3 Sample app with

* CMake
* GSettings
* Localization
* Glade UI file with common callbacks (quit/about)

## Localization

*Scan for translatable text in a Glade file

    xgettext --sort-output --keyword=translatable -o po/sampleapp.pot ui.glade

* Example, for French, copy pot file to fr/sampleapp.po
* Set Content-type with "Content-Type: text/plain; charset=UTF-8\n"

*Create binary file with `msgfmt`

    msgfmt sampleapp.po -o sampleapp.mo

*Testing localization

List installed locals with locals 

    locale -a

Under linux, test by changing the local with

    LANG=fr_FR.utf8 ./bin/sampleapp



