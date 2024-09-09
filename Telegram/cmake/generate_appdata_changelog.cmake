# This file is part of FAgram Desktop,
# the unofficial Telegram client based on tgd.

# For license and copyright information please follow this link:
# https://github.com/fajox1/fagramdesktop/blob/master/LEGAL

function(generate_appdata_changelog target_name changelog_path appdata_path)
    find_package(Python3 REQUIRED)

    set(gen_dst ${CMAKE_CURRENT_BINARY_DIR}/gen)
    file(MAKE_DIRECTORY ${gen_dst})

    set(gen_timestamp ${gen_dst}/${target_name}_appdata_changelog.timestamp)
    set(gen_files ${appdata_path})

    add_custom_command(
    OUTPUT
        ${gen_timestamp}
    COMMAND
        ${Python3_EXECUTABLE}
        ${submodules_loc}/build/changelog2appdata.py
        -c "${changelog_path}"
        -a "${appdata_path}"
        -n 10
    COMMAND
        echo 1> ${gen_timestamp}
    COMMENT "Generating AppData changelog (${target_name})"
    DEPENDS
        ${submodules_loc}/build/changelog2appdata.py
        ${changelog_path}
        ${appdata_path}
    )
    generate_target(${target_name} appdata_changelog ${gen_timestamp} "${gen_files}" ${gen_dst})
endfunction()
