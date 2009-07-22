#!/usr/bin/perl

# You must 'cd' to the top directory of GCompris before you run it

use strict;
use Data::Dumper;

my $gcompris_root_dir = ".";
my $ALL_LINGUAS_STR   = `grep "ALL_LINGUAS=" $gcompris_root_dir/configure.in | cut -d= -f2`;
$ALL_LINGUAS_STR      =~ s/\"//g;
my @ALL_LINGUAS       = split(' ', $ALL_LINGUAS_STR);

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
open (MYFILE, 'nsis_translations.desktop');
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
open (MYFILE, 'gcompris-installer.nsi');
while (<MYFILE>) {
    if ($_ =~ /\@INSERTMACRO_MUI_LANGUAGE\@/)
    {
	print "Processing \@INSERTMACRO_MUI_LANGUAGE\@\n";
	$gcomprisInstaller .= $muiLanguages;
    }
    elsif ($_ =~ /\@GCOMPRIS_MACRO_INCLUDE_LANGFILE\@/)
    {
	print "Processing \@GCOMPRIS_MACRO_INCLUDE_LANGFILE\@\n";
	$gcomprisInstaller .= $gcomprisLanguages;
    }
    else
    {
	$gcomprisInstaller .= "$_";
    }
}
close (MYFILE);

# Rewrite the file with the replaced data
open (MYFILE, '>gcompris-installer.nsi');
print MYFILE "$gcomprisInstaller";
close (MYFILE);

#
# Create each nsh translation file
#

print "Creating the nsh default file\n";
open (DESC, ">nsis/translations/en.nsh");
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
    open (DESC, ">nsis/translations/$lang.nsh");
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
