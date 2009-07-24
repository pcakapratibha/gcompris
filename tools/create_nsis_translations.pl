#!/usr/bin/perl
#
# create_nsis_translations.pl
#
# Copyright (C) 2000-2009 Bruno Coudoin
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, see <http://www.gnu.org/licenses/>.
#

use strict;

sub usage {
    print 'create_nsis_translations.pl translations installer tmp_dir
  translations
     This is an input file that contains all the
     translated strings. If must be formated as a GNU/Linux
     desktop file and contains multiple strings entry.
     For example you must have:
     toBe=To be or not to be
     toBe[fr]=Etre ou ne pas etre

  installer
     This is your nsis installer source file. You must include
     in it the marker @INSERT_TRANSLATIONS@ before you use any
     translation string.
     After that you can use the variable $(toBe) in your file.

  tmp_dir
     This is a directory in which temporary files needed for
     the translation system.
     It will be created if non existant.
     You can remove it once you have created your installer.
';
}

my $translations;
if (! $ARGV[0] || ! -f $ARGV[0])
{
    usage();
}
else
{
    $translations = $ARGV[0];
}

shift;
my $installer;
if (! $ARGV[0] || ! -f $ARGV[0])
{
    usage();
}
else
{
    $installer = $ARGV[0];
}

shift;
my $tmp_dir;
if (! $ARGV[0] )
{
    usage();
}
else
{
    $tmp_dir = $ARGV[0];

    if ( ! -d $tmp_dir )
    {
	mkdir $tmp_dir or die "ERROR: '$tmp_dir' $!\n";
    }
}

print "Processing translation file '$translations'\n";
print "          NSIS source file  '$installer'\n";
print "                Working dir '$tmp_dir'\n";

# Commented out locales that are not available in nsis
my %localeNames = (
  "af", "Afrikaans",
#  "am", "Amharic",
  "ar", "Arabic",
  "bg",	"Bulgarian",
  "br",	"Breton",
  "ca",	"Catalan",
  "cs",	"Czech",
  "da", "Danish",
  "de", "German",
#  "dz",	"Dzongkha",
  "el", "Greek",
  "en", "English",
  "es", "Spanish",
  "eu",	"Basque",
#  "fa", "Persian",
  "fi", "Finnish",
  "fr", "French",
  "ga", "Irish",
#  "gu",	"Gujarati",
  "he",	"Hebrew",
#  "hi",	"Hindi",
  "hr",	"Croatian",
  "hu",	"Hungarian",
  "id",	"Indonesian",
  "it", "Italian",
  "ja",	"Japanese",
#  "ka", "Georgian",
  "ko", "Korean",
  "lt",	"Lithuanian",
  "mk",	"Macedonian",
#  "ml",	"Malayalam",
#  "mr",	"Marathi",
  "ms",	"Malay",
  "nb",	"Norwegian",
#  "ne",	"Nepal",
  "nl",	"Dutch",
  "nn",	"NorwegianNynorsk",
#  "oc",	"Occitan",
#  "pa",	"Punjabi",
  "pl",	"Polish",
  "pt",	"Portuguese",
  "pt_BR", "PortugueseBR",
  "ro",	"Romanian",
  "ru",	"Russian",
 # "rw",	"Kinyarwanda",
  "sk",	"Slovak",
  "sl",	"Slovenian",
#  "so",	"Somali",
  "sq",	"Albanian",
  "sr",	"Serbian",
  "sv",	"Swedish",
#  "ta",	"Tamil",
  "th",	"Thai",
  "tr",	"Turkish",
  "uk", "Ukrainian",
#  "ur",	"Urdu",
#  "vi",	"Vietnamese",
#  "wa",	"Walloon",
  "zh",	"SimpChinese",
  "zh", "TradChinese"
);

my @localeKeys = keys(%localeNames);

# Create the holder for the results
# %result{"locale"}{"stringname"} = result line
print "Parsing nsis_translations.desktop\n";
my %result;

# Create a hash of the keys to translate
open (MYFILE, $translations);
while (<MYFILE>) {
    chomp $_;
    if ($_ =~ /Encoding=UTF-8/)
    {
	next;
    }
    elsif ($_ =~ /^(\w+)=(.*)/)
    {
	my $line = "!define $1 \"$2\"\n";
	$result{"en"}{"$1"} = $line;
    }
    elsif ($_ =~ /^(\w+)\[(\w+)\]=(.*)/)
    {
	my $line = "!define $1 \"$3\"\n";
	$result{"$2"}{"$1"} = $line;
    }
}
close (MYFILE);

# Lets insert the default languages
# in the installer file which means replacing:
#   @INSERTMACRO_MUI_LANGUAGE@
# By the list of locales:
#   !insertmacro MUI_LANGUAGE "French"

my $muiLanguages;
$muiLanguages = '
  ;; English goes first because its the default. The rest are
  ;; in alphabetical order (at least the strings actually displayed
  ;; will be).
  !insertmacro MUI_LANGUAGE "English"
';

foreach my $lang (@localeKeys) {
    if ( $lang eq "en" ) { next; }
    $muiLanguages .= "  !insertmacro MUI_LANGUAGE \"$localeNames{$lang}\"\n";
}

# The specific GCompris translation for the installer
# replacing:
#   @GCOMPRIS_MACRO_INCLUDE_LANGFILE@
# By the list of locales:
#   !insertmacro GCOMPRIS_MACRO_INCLUDE_LANGFILE "ALBANIAN" "${GCOMPRIS_NSIS_INCLUDE_PATH}\translations\albanian.nsh"

my $gcomprisLanguages;

$gcomprisLanguages .= '
;--------------------------------
;Translations
  !define GCOMPRIS_DEFAULT_LANGFILE "${GCOMPRIS_NSIS_INCLUDE_PATH}\\translations\\en.nsh"
;;
;; Windows Gcompris NSIS installer language macros
;;

!macro GCOMPRIS_MACRO_DEFAULT_STRING LABEL VALUE
  !ifndef "${LABEL}"
    !define "${LABEL}" "${VALUE}"
    !ifdef INSERT_DEFAULT
      !warning "${LANG} lang file mising ${LABEL}, using default.."
    !endif
  !endif
!macroend

!macro GCOMPRIS_MACRO_LANGSTRING_INSERT LABEL LANG
  LangString "${LABEL}" "${LANG_${LANG}}" "${${LABEL}}"
  !undef "${LABEL}"
!macroend

!macro GCOMPRIS_MACRO_LANGUAGEFILE_BEGIN LANG
  !define CUR_LANG "${LANG}"
!macroend
';


# GCOMPRIS_MACRO_LANGUAGEFILE_END
$gcomprisLanguages .= '
!macro GCOMPRIS_MACRO_LANGUAGEFILE_END
  !define INSERT_DEFAULT
  !include "${GCOMPRIS_DEFAULT_LANGFILE}"
  !undef INSERT_DEFAULT

  ; String labels should match those from the default language file.
';

my $text_en = $result{"en"};
foreach my $keyEn (keys(%$text_en)) {
    $gcomprisLanguages .= "  !insertmacro GCOMPRIS_MACRO_LANGSTRING_INSERT $keyEn \${CUR_LANG}";
    $gcomprisLanguages .= "\n";
}

$gcomprisLanguages .= '
  !undef CUR_LANG
!macroend
';

$gcomprisLanguages .= '
!macro GCOMPRIS_MACRO_INCLUDE_LANGFILE LANG FILE
  !insertmacro GCOMPRIS_MACRO_LANGUAGEFILE_BEGIN "${LANG}"
  !include "${FILE}"
  !insertmacro GCOMPRIS_MACRO_LANGUAGEFILE_END
!macroend
';

foreach my $lang (@localeKeys) {
    $gcomprisLanguages .= "  !insertmacro GCOMPRIS_MACRO_INCLUDE_LANGFILE".
     " \"$localeNames{$lang}\"".
     " \"\${GCOMPRIS_NSIS_INCLUDE_PATH}\\translations\\$lang.nsh\"\n";
}

# We have all the data, let's replace it
my $gcomprisInstaller;
open (MYFILE, $installer);
while (<MYFILE>) {
    if ($_ =~ /\@INSERT_TRANSLATIONS\@/)
    {
	print "Processing \@INSERT_TRANSLATIONS\@\n";
	$gcomprisInstaller .= $muiLanguages;
	$gcomprisInstaller .= $gcomprisLanguages;
    }
    else
    {
	$gcomprisInstaller .= "$_";
    }
}
close (MYFILE);

# Rewrite the file with the replaced data
open (MYFILE, ">$installer");
print MYFILE "$gcomprisInstaller";
close (MYFILE);

#
# Create each nsh translation file
#

print "Creating the nsh default file\n";
open (DESC, ">$tmp_dir/en.nsh");
print DESC ";; Auto generated file by create_nsis_translations.pl\n";
foreach my $keyEn (keys(%$text_en)) {
    my $line = $result{'en'}{$keyEn};
    $line =~ s/!define /!insertmacro GCOMPRIS_MACRO_DEFAULT_STRING /;
    print DESC $line;
}
close DESC;

print "Creating the nsh locale files\n";
foreach my $lang (@localeKeys) {
    if ( $lang eq "en" ) { next; }
    open (DESC, ">$tmp_dir/$lang.nsh");
    print DESC ";; Auto generated file by create_nsis_translations.pl\n";

    my $text_locale = $result{"$lang"};
    foreach my $keyEn (keys(%$text_en)) {
	my $found = 0;
	foreach my $keyLocale (keys(%$text_locale)) {
	    # Fine, we found a translation
	    if ( $keyLocale eq $keyEn )
	    {
		print DESC "$result{$lang}{$keyLocale}";
		$found = 1;
		last;
	    }
	}
	# English keys are the reference.
	# If not found they are inserted
	if ( ! $found )
	{
	    print DESC "$result{'en'}{$keyEn}";
	}
    }
    close DESC;
}
