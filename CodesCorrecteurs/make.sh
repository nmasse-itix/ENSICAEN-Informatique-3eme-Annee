#!/bin/sh

set -e

latex ss-cc.tex
dvips ss-cc.dvi -o ss-cc.ps

# This line works as follows: the -pa4 tells pstops to use a4 paper.
# THe 6: tells it that it will be working with 6 pages.
# The 0R@$scale($xpos,0.66h) part works as follows:
# 0R@scale tells it to work on the zeroth page, rotate it right, and scale it 
# by $scale.
# The ($xpos,0.66h) part gives the x and y offsets, telling where 
# to place the page on the sheet of paper.  

# You may need to fiddle with these offsets, in particular, to 
# suit your printer.  This works for an HP400 deskjet.

# Copyright Nels Tomlinson, 2001, 2003. 
# You may freely distribute this file, provided that the copyright notice and this permission notice are retained.

# Modified by Carlos Gonzalez-Alcon to use an A4 paper. Oct 2003.
# Modified by Nicolas MASSE to use 6 columns. 2007.

paper="a4"
scale="1.0"
xpos="-3.4in"

pstops -p$paper  "6:1R@$scale($xpos,1.0h)+2R@$scale($xpos,0.66h)+3R@$scale($xpos,0.33h),0R@$scale($xpos,0.33h)+5R@$scale($xpos,0.66h)+4R@$scale($xpos,1.0h)" ss-cc.ps ss-cc.$paper.ps


ps2pdf14 -sPAPERSIZE=$paper ss-cc.$paper.ps

