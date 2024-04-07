# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/lucia/programacao/My project/MultiplayerBook/PDCursesMod-master-build/zlib"
  "C:/Users/lucia/programacao/My project/MultiplayerBook/PDCursesMod-master-build/zlib_ext-prefix/src/zlib_ext-build"
  "C:/Users/lucia/programacao/My project/MultiplayerBook/PDCursesMod-master-build/zlib_ext-prefix"
  "C:/Users/lucia/programacao/My project/MultiplayerBook/PDCursesMod-master-build/zlib_ext-prefix/tmp"
  "C:/Users/lucia/programacao/My project/MultiplayerBook/PDCursesMod-master-build/zlib_ext-prefix/src/zlib_ext-stamp"
  "C:/Users/lucia/programacao/My project/MultiplayerBook/PDCursesMod-master-build"
  "C:/Users/lucia/programacao/My project/MultiplayerBook/PDCursesMod-master-build/zlib_ext-prefix/src/zlib_ext-stamp"
)

set(configSubDirs Debug;Release;MinSizeRel;RelWithDebInfo)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/lucia/programacao/My project/MultiplayerBook/PDCursesMod-master-build/zlib_ext-prefix/src/zlib_ext-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/lucia/programacao/My project/MultiplayerBook/PDCursesMod-master-build/zlib_ext-prefix/src/zlib_ext-stamp${cfgdir}") # cfgdir has leading slash
endif()
