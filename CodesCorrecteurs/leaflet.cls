%%
%% This is file `leaflet.cls',
%% generated with the docstrip utility.
%%
%% The original source files were:
%%
%% leaflet.dtx  (with options: `class')
%% 
%%   Copyright 1998 Juergen Schlegelmilch
%% 
%%   This program is provided under the terms of the
%%   LaTeX Project Public License distributed from CTAN
%%   archives in directory macros/latex/base/lppl.txt.
%% 
%%   Author: Juergen Schlegelmilch
%%           schlegel@informatik.uni-rostock.de
%% 
\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{leaflet}[1999/06/01 v0.3 document class leaflet]
\LoadClassWithOptions{article}
\newlength{\p@perwidth}
\setlength{\p@perwidth}{0.333333334\paperheight}
\newlength{\p@perheight}
\setlength{\p@perheight}{\paperwidth}
\RequirePackage{geometry}
\geometry{papersize={\p@perwidth,\p@perheight},
        vmargin=10mm,hmargin=8mm,
        noheadfoot,
        marginparwidth=0mm,marginparsep=0mm}
\newcommand\customhead{}
\newcommand\customfoot{}
\newcommand\ps@leaflet{%
 \def\@evenhead{%
   \customhead\hfill}%
 \def\@oddhead{%
   \ifnum\c@page=\tw@
    {\unitlength1mm
    % set the fold mark at 8mm (left margin) + 91mm
    \begin{picture}(0,0)\put(91,0){\rule{0.3mm}{0.3mm}}\end{picture}}%
   \fi
   \ifnum\c@page=7\ClassError{leaflet}{%
      Too much text for leaflet}{%
      The text you supplied fills more than six pages and will
      therefore not fit onto a single leaflet. Try using smaller
      fonts or reducing vertical space.}\fi
   \customhead
   \hfill}%
 \def\@evenfoot{\customfoot\hfill}%
 \let\@oddfoot\@evenfoot
 }
\pagestyle{leaflet}
\sloppy
\setcounter{secnumdepth}{0}
\let\tempitemize=\itemize
\renewcommand\itemize{%
 \setlength{\topsep}{0pt}%
 \setlength{\partopsep}{0pt}%
 \tempitemize
 \setlength{\parskip}{0pt}%
 \setlength{\parsep}{0pt}%
 \setlength{\itemsep}{0pt}}
\let\tempenumerate=\enumerate
\renewcommand\enumerate{%
 \setlength{\topsep}{0pt}%
 \setlength{\partopsep}{0pt}%
 \tempenumerate
 \setlength{\parskip}{0pt}%
 \setlength{\parsep}{0pt}%
 \setlength{\itemsep}{0pt}}
\let\tempdescription=\description
\renewcommand\description{%
 \setlength{\topsep}{0pt}%
 \setlength{\partopsep}{0pt}%
 \tempdescription
 \setlength{\parskip}{0pt}%
 \setlength{\parsep}{0pt}%
 \setlength{\itemsep}{0pt}}
\setlength{\leftmargini}{1.2em}
\setlength{\leftmarginii}{1.6em}
\setlength{\leftmarginiii}{1.2em}
\setlength{\leftmarginiv}{1.2em}
\renewcommand\topfraction{0.7}
\renewcommand\bottomfraction{0.7}
\setlength{\textfloatsep}{10pt plus 4pt minus 3pt}
\renewcommand\section{%
 \@startsection{section}{3}{\z@}%
    {-2.75ex\@plus -1ex \@minus -.2ex}%
    {0.2ex \@plus .1ex}%
    {\normalfont\large\bfseries}}%
\renewcommand\subsection{%
 \@startsection{subsection}{4}{\z@}%
    {-0.75ex \@minus -.5ex}%
    {0.2ex \@plus .1ex}%
    {\normalfont\normalsize\bfseries}}%
\let\subsubsetion=\subsection
\renewcommand\paragraph{%
 \@startsection{paragraph}{4}{\z@}%
    {0.75ex \@plus1ex \@minus.2ex}%
    {-1em}%
    {\normalfont\normalsize\bfseries}}
\renewcommand\subparagraph{%
 \@startsection{paragraph}{4}{\z@}%
    {0.2ex \@minus.2ex}%
    {-1em}%
    {\normalfont\normalsize\bfseries}}
\let\part=\relax
\let\chapter=\relax
\endinput
%%
%% End of file `leaflet.cls'.
