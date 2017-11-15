# GTK3 Sample app using

* CMake
* GSettings
* Localization
* Glade UI file with common callbacks (quit/about)


# Build (linux)

For instruction on building under Windows, see Windows.md

<pre>
--generate Makefile and config.h
$cmake .
--generate binary
$make
--install files, settings and binaries
#make install
</pre>

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
