normalize() {
    local safe=${1//[^[:alnum:]]/}
    echo "${safe,,}"
}

PROJECT_NAME="sampleapp"
NEW_PROJECT_NAME= normalize $1
sed -i -e "s/$PROJECT_NAME/$NEW_PROJECT_NAME/g" CMakeLists.txt $PROJECT_NAME.desktop $PROJECT_NAME/ui/$PROJECT_NAME.ui
mv po/$PROJECT_NAME.pot po/$NEW_PROJECT_NAME.pot
mv po/fr/$PROJECT_NAME.po po/fr/$NEW_PROJECT_NAME.po
mv po/fr/$PROJECT_NAME.mo po/fr/$NEW_PROJECT_NAME.mo
mv $PROJECT_NAME/$PROJECT_NAME.png $PROJECT_NAME/NEW_PROJECT_NAME.png
mv $PROJECT_NAME/ui/$PROJECT_NAME.ui $PROJECT_NAME/ui/NEW_PROJECT_NAME.ui
mv share/share/glib-2.0/schemas/$PROJECT_NAME.xml share/share/glib-2.0/schemas/$NEW_PROJECT_NAME.xml
mv $PROJECT_NAME $NEW_PROJECT_NAME
