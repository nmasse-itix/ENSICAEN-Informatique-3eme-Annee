for i in filmographie resumes resume aliases alias perso nom naissance mort biblio p mariages mariage infos info citations citation roles role; do echo '<!ELEMENT' "$i ANY>"; done > film.dtd

xmllint --valid --noout minibergman.xml 2>&1 |grep minibergman.xml |sed -r 's/.*attribute ([^ ]+) of element ([^ ]+)/\1 \2/' |sort |uniq > listeAtts

for i in $(awk '{print $2}' < listeAtts |sort |uniq) ; do echo -n '<!ATTLIST' "$i "; for j in $(awk "\$2 == \"$i\" {print \$1}" < listeAtts); do echo -n "$j CDATA #IMPLIED " ; done ; echo ">"; done >>film.dtd

