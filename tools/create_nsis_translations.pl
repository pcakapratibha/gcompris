#!/usr/bin/perl

# You must 'cd' to the top directory of GCompris before you run it

use strict;

my $gcompris_root_dir = ".";
my $ALL_LINGUAS_STR   = `grep "ALL_LINGUAS=" $gcompris_root_dir/configure.in | cut -d= -f2`;
$ALL_LINGUAS_STR      =~ s/\"//g;
my @ALL_LINGUAS       = split(' ', $ALL_LINGUAS_STR);

my %localeNames = (
  "af", "Afrikaans",
  "am", "Amharic",
  "ar", "Arabic",
  "az", "Turkish",
  "bg",	"Bulgarian",
  "br",	"Breton",
  "ca",	"Catalan",
  "cs",	"Czech",
  "da", "Danish",
  "de", "German",
  "dz",	"Dzongkha",
  "el", "Greek",
  "es", "Spanish",
  "eu",	"Basque",
  "fa", "Persian",
  "fi", "Finnish",
  "fr", "French",
  "ga", "Irish",
  "gu",	"Gujarati",
  "he",	"Hebrew",
  "hi",	"Hindi",
  "hr",	"Croatian",
  "hu",	"Hungarian",
  "id",	"Indonesian",
  "it", "Italian",
  "ja",	"Japanese",
  "ka", "Georgian",
  "ko", "Korean",
  "lt",	"Lithuanian",
  "mk",	"Macedonian",
  "ml",	"Malayalam",
  "mr",	"Marathi",
  "ms",	"Malay",
  "nb",	"Norwegian Bokmal",
  "ne",	"Nepal",
  "nl",	"Dutch",
  "nn",	"Norwegian Nynorsk",
  "oc",	"Occitan",
  "pa",	"Punjabi",
  "pl",	"Polish",
  "pt",	"Portuguese",
  "pt_BR", "PortugueseBR",
  "ro",	"Romanian",
  "ru",	"Russian",
  "rw",	"Kinyarwanda",
  "sk",	"Slovak",
  "sl",	"Slovenian",
  "so",	"Somali",
  "sq",	"Albanian",
  "sr",	"Serbian",
  "sv",	"Swedish",
  "ta",	"Tamil",
  "th",	"Thai",
  "tr",	"Turkish",
  "uk", "Ukrainian",
  "ur",	"Urdu",
  "vi",	"Vietnamese",
  "wa",	"Walloon",
  "zh",	"SimpChinese",
  "zh", "TradChinese"
);

my @localeKeys = keys(%localeNames);

# Lets insert the default languages
# in the installer file which means replacing:
#   @INSERTMACRO_MUI_LANGUAGE@
# By the list of locales:
#   !insertmacro MUI_LANGUAGE "French"

my $muiLanguages;
foreach my $lang (@localeKeys) {
    $muiLanguages .= "  !insertmacro MUI_LANGUAGE \"$localeNames{$lang}\"\n";
}

print $muiLanguages;

# The specific GCompris translation for the installer
# replacing:
#   @GCOMPRIS_MACRO_INCLUDE_LANGFILE@
# By the list of locales:
#   !insertmacro GCOMPRIS_MACRO_INCLUDE_LANGFILE "ALBANIAN" "${GCOMPRIS_NSIS_INCLUDE_PATH}\translations\albanian.nsh"

my $gcomprisLanguages;
foreach my $lang (@localeKeys) {
    $gcomprisLanguages .= "  !insertmacro GCOMPRIS_MACRO_INCLUDE_LANGFILE".
     " \"$localeNames{$lang}\"".
     "\"\${GCOMPRIS_NSIS_INCLUDE_PATH}\\translations\\$lang.nsh\"\n";
}

print $gcomprisLanguages;

# Create each nsh translation file

foreach my $lang (@localeKeys) {
    open (DESC, ">nsis/tt/$lang.nsh");
    print DESC ";; Auto generated file by create_nsis_translations.pl\n";

    # Extract the string to translate from the nsis_translations file
    my @text = `grep "\\\[$lang\\\]" $gcompris_root_dir/nsis_translations.desktop`;

    foreach my $line (@text) {
        chomp $line;
        my @keyval = split("=", $line);
        print DESC "@keyval[0]=\"@keyval[1]\"\n";
    }
    close DESC;
}
