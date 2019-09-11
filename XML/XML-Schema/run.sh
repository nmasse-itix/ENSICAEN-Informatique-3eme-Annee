#!/bin/sh

#
# Schema 1
#

# Test 1
echo
echo ">>> Validation of 'test1.xml' against 'local.xsd'... "
echo
xmllint --noout --schema local.xsd test1.xml

# Test 2
echo
echo ">>> Validation of 'test2.xml' against 'local.xsd'... "
echo
xmllint --noout --schema local.xsd test2.xml

#
# Schema 2
#

# Test 3
echo
echo ">>> Validation of 'test3.xml' against 'global.xsd'... "
echo
xmllint --noout --schema global.xsd test3.xml

# Test 4
echo
echo ">>> Validation of 'test4.xml' against 'global.xsd'... "
echo
xmllint --noout --schema global.xsd test4.xml
