script.on_nth_tick(5, function()
    for index, player in pairs(game.connected_players) do
        local info = "XYZ, Player, sUrface, Server\n"
        info = info .. "x: " .. player.position.x .. "\n"
        info = info .. "y: " .. player.position.y .. "\n"
        info = info .. "z: " .. 0 .. "\n"
        info = info .. "p: " .. index .. "\n"
        info = info .. "u: " .. player.surface.index .. "\n"
        info = info .. "s: " .. game.get_player(1).name .. "\n"
        game.write_file("mumble_positional-audio_information.txt", info, false, player.index)
    end
end)
