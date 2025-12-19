#ifndef LOGO_H
#define LOGO_H

#define LOGO                                                                   \
  "    ___\n"                                                                  \
  "   (.. |\n"                                                                 \
  "   (<> |\n"                                                                 \
  "  / __  \\\n"                                                               \
  " ( /  \\ /|\n"                                                              \
  "_/\\ __)/\n"                                                                \
  "\\/-____\\/\n"

#if defined(__linux__)

#elif defines(__APPLE__)
#define NAME "MacOS"
#undef LOGO
#define LOGO                                                                   \
  "                                 ____  _____\n"                             \
  "           ____ ___  ____  _____/ __ \\/ ___/\n"                            \
  "          / __ `__ \\/ __ `/ ___/ / / /\\__ \\\n"                           \
  "         / / / / / / /_/ / /__/ /_/ /___/ /\n"                              \
  "        /_/ /_/ /_/\\__,_/\\___/\\____//____/\n"
#endif

#endif // LOGO_H
