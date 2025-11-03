#pragma once

#include <libintl.h>
#include <locale.h>

// CURRENTLY NOT IMPLEMENTED

// #define _(string) gettext(string)
// #define _d(domain, string) dgettext(domain, string)
// #define _dc(domain, string, category) dcgettext(domain, string, category)

#define _(string) string
#define _d(domain, string) string
#define _dc(domain, string, category) string