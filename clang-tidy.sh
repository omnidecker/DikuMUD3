#!/bin/bash

#https://clang.llvm.org/extra/clang-tidy/checks/modernize-redundant-void-arg.html

tidy_binary=clang-tidy-12
which ${tidy_binary} > /dev/null 2>&1
if [ $? -ne 0 ]; then
   echo -e "\n\nERROR: clang-tidy needs to be installed"
   echo -e "\n    sudo apt-get install clang-tidy-12\n\n"
   if [ "$1" = "FEDORA" ]; then
      tidy_binary=clang-tidy
   else
      exit 1
   fi
fi

sources="
vme/src/OutputCapture.cpp
vme/src/OutputCapture.h
vme/src/account.cpp
vme/src/account.h
vme/src/act_change.cpp
vme/src/act_change.h
vme/src/act_color.cpp
vme/src/act_color.h
vme/src/act_info.cpp
vme/src/act_info.h
vme/src/act_movement.cpp
vme/src/act_movement.h
vme/src/act_offensive.cpp
vme/src/act_offensive.h
vme/src/act_other.cpp
vme/src/act_other.h
vme/src/act_skills.cpp
vme/src/act_skills.h
vme/src/act_wizard.cpp
vme/src/act_wizard.h
vme/src/act_wstat.cpp
vme/src/act_wstat.h
vme/src/affect.cpp
vme/src/affect.h
vme/src/affectdil.h
vme/src/apf_affect.cpp
vme/src/apf_affect.h
vme/src/badnames.cpp
vme/src/badnames.h
vme/src/ban.cpp
vme/src/ban.h
vme/src/bank.cpp
vme/src/bank.h
vme/src/bytestring.cpp
vme/src/bytestring.h
vme/src/char_point_data.cpp
vme/src/char_point_data.h
vme/src/cmdload.cpp
vme/src/cmdload.h
vme/src/color.cpp
vme/src/color.h
vme/src/combat.cpp
vme/src/combat.h
vme/src/comm.cpp
vme/src/comm.h
vme/src/common.cpp
vme/src/common.h
vme/src/compile_defines.h
vme/src/config.cpp
vme/src/config.h
vme/src/constants.cpp
vme/src/constants.h
vme/src/convert.cpp
vme/src/convert.h
vme/src/db.cpp
vme/src/db.h
vme/src/db_file.cpp
vme/src/db_file.h
vme/src/dbfind.cpp
vme/src/dbfind.h
vme/src/defcomp/defcomp.cpp
vme/src/defcomp/defcomp.h
vme/src/defcomp/main.cpp
vme/src/descriptor_data.cpp
vme/src/descriptor_data.h
vme/src/destruct.cpp
vme/src/destruct.h
vme/src/dictionary.cpp
vme/src/dictionary.h
vme/src/diku_exception.h
vme/src/dil.h
vme/src/dilexp.cpp
vme/src/dilexp.h
vme/src/dilfld.cpp
vme/src/dilinst.cpp
vme/src/dilinst.h
vme/src/dilrun.cpp
vme/src/dilrun.h
vme/src/dilshare.cpp
vme/src/dilshare.h
vme/src/dilsup.cpp
vme/src/dilsup.h
vme/src/eliza.cpp
vme/src/eliza.h
vme/src/error.h
vme/src/essential.h
vme/src/event.cpp
vme/src/event.h
vme/src/experience.cpp
vme/src/experience.h
vme/src/extra.cpp
vme/src/extra.h
vme/src/fight.cpp
vme/src/fight.h
vme/src/file_index_type.cpp
vme/src/file_index_type.h
vme/src/files.cpp
vme/src/files.h
vme/src/formatter.h
vme/src/guild.cpp
vme/src/guild.h
vme/src/handler.cpp
vme/src/handler.h
vme/src/hook.cpp
vme/src/hook.h
vme/src/hookmud.cpp
vme/src/hookmud.h
vme/src/interpreter.cpp
vme/src/interpreter.h
vme/src/intlist.cpp
vme/src/intlist.h
vme/src/justice.cpp
vme/src/justice.h
vme/src/magic.cpp
vme/src/magic.h
vme/src/main.cpp
vme/src/main.h
vme/src/main_functions.cpp
vme/src/main_functions.h
vme/src/membug.cpp
vme/src/membug.h
vme/src/mobact.cpp
vme/src/mobact.h
vme/src/modify.cpp
vme/src/modify.h
vme/src/money.cpp
vme/src/money.h
vme/src/movement.h
vme/src/mplex/ClientConnector.cpp
vme/src/mplex/ClientConnector.h
vme/src/mplex/MUDConnector.cpp
vme/src/mplex/MUDConnector.h
vme/src/mplex/echo_server.cpp
vme/src/mplex/echo_server.h
vme/src/mplex/main.cpp
vme/src/mplex/mplex.cpp
vme/src/mplex/mplex.h
vme/src/mplex/network.cpp
vme/src/mplex/network.h
vme/src/mplex/telnet.h
vme/src/mplex/translate.cpp
vme/src/mplex/translate.h
vme/src/mplex/ttydef.h
vme/src/namelist.cpp
vme/src/namelist.h
vme/src/nanny.cpp
vme/src/nanny.h
vme/src/nice.cpp
vme/src/nice.h
vme/src/path.cpp
vme/src/path.h
vme/src/pcsave.cpp
vme/src/pcsave.h
vme/src/pipe.cpp
vme/src/pipe.h
vme/src/protocol.cpp
vme/src/protocol.h
vme/src/queue.cpp
vme/src/queue.h
vme/src/reception.cpp
vme/src/reception.h
vme/src/sector.cpp
vme/src/sector.h
vme/src/signals.cpp
vme/src/signals.h
vme/src/skills.cpp
vme/src/skills.h
vme/src/slime.cpp
vme/src/slime.h
vme/src/slog.h
vme/src/slog_raw.cpp
vme/src/slog_raw.h
vme/src/snoop_data.cpp
vme/src/snoop_data.h
vme/src/spec_assign.cpp
vme/src/spec_assign.h
vme/src/spec_procs.cpp
vme/src/spec_procs.h
vme/src/spell_parser.cpp
vme/src/spell_parser.h
vme/src/spells.h
vme/src/str_parse.cpp
vme/src/str_parse.h
vme/src/structs.cpp
vme/src/structs.h
vme/src/system.cpp
vme/src/system.h
vme/src/szonelog.h
vme/src/szonelog_raw.cpp
vme/src/szonelog_raw.h
vme/src/t_array.h
vme/src/teach.cpp
vme/src/teach.h
vme/src/textutil.cpp
vme/src/textutil.h
vme/src/tif_affect.cpp
vme/src/tif_affect.h
vme/src/time_info_data.cpp
vme/src/time_info_data.h
vme/src/trie.cpp
vme/src/trie.h
vme/src/unit_affected_type.cpp
vme/src/unit_affected_type.h
vme/src/unit_dil_affected_type.cpp
vme/src/unit_dil_affected_type.h
vme/src/unit_fptr.cpp
vme/src/unit_fptr.h
vme/src/unitfind.cpp
vme/src/unitfind.h
vme/src/utility.cpp
vme/src/utility.h
vme/src/utils.h
vme/src/vmc/dilpar.h
vme/src/vmc/main.cpp
vme/src/vmc/vmc.cpp
vme/src/vmc/vmc.h
vme/src/vmc/vmc_process.cpp
vme/src/vmc/vmc_process.h
vme/src/vmelimits.cpp
vme/src/vmelimits.h
vme/src/weather.cpp
vme/src/weather.h
vme/src/zon_basis.cpp
vme/src/zon_basis.h
vme/src/zon_wiz.cpp
vme/src/zon_wiz.h
vme/src/zone_reset.cpp
vme/src/zone_reset.h
vme/src/zone_reset_cmd.cpp
vme/src/zone_reset_cmd.h
vme/src/zone_type.cpp
vme/src/zone_type.h
"

# Create clean fresh compile_commands.json file for clang-tidy
tmpdir=$(mktemp -d -p .)
pushd $tmpdir
cmake ..
popd

for source in $sources
do
   echo "Selecting [$source] for tidying!"
   ${tidy_binary} -p $tmpdir --quiet --checks="-*,readability-braces-around-statements,modernize-use-nullptr,readability-isolate-declaration,cppcoreguidelines-init-variables,modernize-redundant-void-arg" --fix $source || exit 1
   clang-format -i $source
done
rm -rf $tmpdir
echo -e "\n\nFINISHED!\n\n"