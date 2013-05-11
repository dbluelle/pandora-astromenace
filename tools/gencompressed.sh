#!/bin/sh

TEXTOOL=/opt/develop/pandora/PowerVRSDK/PVRTexTool/CL/Linux_x86_64/PVRTexToolCL
RAW_DATA=/opt/develop/pandora/native/openastromenace-code/rawdecomp/
POWERVR_DATA=/opt/develop/pandora/native/openastromenace-code/RAW_VFS_DATA_POWERVR/
rm -f -r $POWERVR_DATA
mkdir $POWERVR_DATA
cp -r $RAW_DATA* $POWERVR_DATA

convert_ogg_wav() {
	sox $POWERVR_DATA/RAW_VFS_DATA/$1 $POWERVR_DATA/RAW_VFS_DATA/$1.wav
	mv $POWERVR_DATA/RAW_VFS_DATA/$1.wav $POWERVR_DATA/RAW_VFS_DATA/$1
}

convert_tga_rgba() {
	convert $POWERVR_DATA/RAW_VFS_DATA/$1 PNG32:$POWERVR_DATA/RAW_VFS_DATA/$1.png
	#mogrify -resize 50% $f2.png
	$TEXTOOL -i $POWERVR_DATA/RAW_VFS_DATA/$1.png -o $POWERVR_DATA/RAW_VFS_DATA/$1.pvr -m -f PVRTC1_2 -pot -flip y -square
	mv $POWERVR_DATA/RAW_VFS_DATA/$1.pvr $POWERVR_DATA/RAW_VFS_DATA/$1
}
convert_tga_rgb() {
	convert $POWERVR_DATA/RAW_VFS_DATA/$1 PNG24:$POWERVR_DATA/RAW_VFS_DATA/$1.png
	#mogrify -resize 50% $f2.png
	$TEXTOOL -i $POWERVR_DATA/RAW_VFS_DATA/$1.png -o $POWERVR_DATA/RAW_VFS_DATA/$1.pvr -m -f PVRTC1_2 -pot -flip y -square
	mv $POWERVR_DATA/RAW_VFS_DATA/$1.pvr $POWERVR_DATA/RAW_VFS_DATA/$1
}
convert_vw2d() {
	mogrify -resize x64 PNG24:$POWERVR_DATA/RAW_VFS_DATA/$1.png
	$TEXTOOL -i $POWERVR_DATA/RAW_VFS_DATA/$1.png -o $POWERVR_DATA/RAW_VFS_DATA/$1.pvr -m -f PVRTC1_2 -pot -flip y -square
	mv $POWERVR_DATA/RAW_VFS_DATA/$1.pvr $POWERVR_DATA/RAW_VFS_DATA/$1
}
convert_tga_minimal() {
	convert $POWERVR_DATA/RAW_VFS_DATA/$1 -resize 32^ PNG24:$POWERVR_DATA/RAW_VFS_DATA/$1.png
	$TEXTOOL -i $POWERVR_DATA/RAW_VFS_DATA/$1.png -o $POWERVR_DATA/RAW_VFS_DATA/$1.pvr -m -f PVRTC1_2 -pot -flip y -square
	mv $POWERVR_DATA/RAW_VFS_DATA/$1.pvr $POWERVR_DATA/RAW_VFS_DATA/$1
}
convert_tga_minimal_rgba() {
	convert $POWERVR_DATA/RAW_VFS_DATA/$1 -resize 32^ PNG32:$POWERVR_DATA/RAW_VFS_DATA/$1.png
	$TEXTOOL -i $POWERVR_DATA/RAW_VFS_DATA/$1.png -o $POWERVR_DATA/RAW_VFS_DATA/$1.pvr -m -f PVRTC1_2 -pot -flip y -square
	mv $POWERVR_DATA/RAW_VFS_DATA/$1.pvr $POWERVR_DATA/RAW_VFS_DATA/$1
}
convert_tga_transp() {
	convert $POWERVR_DATA/RAW_VFS_DATA/$1 \( +clone \) -alpha off -compose copy_opacity -composite -resize 32^ $POWERVR_DATA/RAW_VFS_DATA/$1.png
	$TEXTOOL -i $POWERVR_DATA/RAW_VFS_DATA/$1.png -o $POWERVR_DATA/RAW_VFS_DATA/$1.pvr -m -f PVRTC1_2 -pot -flip y -square
	mv $POWERVR_DATA/RAW_VFS_DATA/$1.pvr $POWERVR_DATA/RAW_VFS_DATA/$1
}


convert_tga_rgba "/CREDITS/sdl.tga"
convert_tga_rgba "/CREDITS/svn.tga"
convert_tga_rgba "/CREDITS/opengl.tga"
convert_tga_rgba "/CREDITS/openal.tga"
convert_tga_rgba "/CREDITS/codeblocks.tga"
convert_tga_rgba "/CREDITS/gnugcc.tga"
convert_tga_rgba "/CREDITS/gentoo.tga"
convert_tga_rgba "/CREDITS/freetype.tga"
convert_tga_rgba "/CREDITS/oggvorbis.tga"
convert_tga_rgba "/CREDITS/gimp.tga"
convert_tga_rgb "/DATA_DE/MENU/button_weaponry_out.tga"
convert_tga_rgb "/DATA_DE/MENU/button_weaponry_in.tga"
convert_tga_rgb "/DATA_EN/MENU/button_weaponry_out.tga"
convert_tga_rgb "/DATA_EN/MENU/button_weaponry_in.tga"
convert_tga_rgb "/DATA_RU/MENU/button_weaponry_out.tga"
convert_tga_rgb "/DATA_RU/MENU/button_weaponry_in.tga"
convert_tga_rgba "/DATA_DE/GAME/pause.tga"
convert_tga_rgba "/DATA_DE/GAME/mission.tga"
convert_tga_rgba "/DATA_DE/GAME/missionfailed.tga"
convert_tga_rgba "/DATA_EN/GAME/pause.tga"
convert_tga_rgba "/DATA_EN/GAME/mission.tga"
convert_tga_rgba "/DATA_EN/GAME/missionfailed.tga"
convert_tga_rgba "/DATA_RU/GAME/pause.tga"
convert_tga_rgba "/DATA_RU/GAME/mission.tga"
convert_tga_rgba "/DATA_RU/GAME/missionfailed.tga"
convert_tga_rgba "/GAME/nums.tga"
convert_tga_minimal_rgba "/GAME/ammo.tga"
convert_tga_minimal_rgba "/GAME/energy.tga"
convert_tga_rgba "/GAME/game_panel.tga"
convert_tga_rgba "/GAME/game_panel2.tga"
convert_tga_rgba "/GAME/game_panel_el.tga"
convert_tga_rgba "/GAME/game_num.tga"
convert_tga_rgba "/GAME/weapon_panel_left.tga"
convert_tga_rgba "/GAME/weapon_panel_right.tga"
convert_tga_minimal_rgba "/GAME/weapon_ammo.tga"
convert_tga_minimal_rgba "/GAME/weapon_energy.tga"
convert_tga_transp "/GFX/flare.tga"
convert_tga_minimal_rgba "/GFX/flare1.tga"
convert_tga_minimal_rgba "/GFX/flare2.tga"
convert_tga_minimal_rgba "/GFX/flare3.tga"
convert_tga_minimal_rgba "/GFX/trail1.tga"
convert_tga_minimal_rgba "/GFX/trail2.tga"
convert_tga_minimal_rgba "/GFX/trail3.tga"
convert_tga_minimal_rgba "/GFX/trail4.tga"
convert_tga_minimal_rgba "/GFX/trail5.tga"
convert_tga_rgb "/LOADING/viewizardlogo.tga"
convert_tga_rgba "/LOADING/loading_back.tga"
convert_tga_rgba "/LOADING/loading_line.tga"
convert_tga_rgb "/LOADING/loading01.tga"
convert_tga_rgb "/LOADING/loading02.tga"
convert_tga_rgb "/LOADING/loading03.tga"
convert_tga_rgb "/LOADING/loading04.tga"
convert_tga_rgba "/MENU/astromenace.tga"
convert_tga_rgba "/MENU/button384_back.tga"
convert_tga_rgba "/MENU/button384_in.tga"
convert_tga_rgba "/MENU/button384_out.tga"
convert_tga_rgba "/MENU/button256_back.tga"
convert_tga_rgba "/MENU/button256_in.tga"
convert_tga_rgba "/MENU/button256_out.tga"
convert_tga_rgba "/MENU/button256_off.tga"
convert_tga_rgba "/MENU/workshop_panel1.tga"
convert_tga_rgba "/MENU/workshop_panel1+.tga"
convert_tga_rgba "/MENU/workshop_panel2.tga"
convert_tga_rgba "/MENU/workshop_panel2+.tga"
convert_tga_rgba "/MENU/workshop_panel3.tga"
convert_tga_rgba "/MENU/workshop_panel4.tga"
convert_tga_rgba "/MENU/workshop_panel5.tga"
convert_tga_minimal "/MENU/blackpoint.tga"
convert_tga_minimal "/MENU/whitepoint.tga"
convert_tga_rgba "/MENU/line.tga"
convert_tga_rgba "/MENU/perc.tga"
convert_tga_rgba "/MENU/perc_none.tga"
convert_tga_rgba "/MENU/checkbox_main.tga"
convert_tga_rgba "/MENU/checkbox_in.tga"
convert_tga_rgba "/MENU/ammo.tga"
convert_tga_rgba "/MENU/back_spot.tga"
convert_tga_rgba "/MENU/back_spot2.tga"
convert_tga_rgba "/MENU/dialog512_256.tga"
convert_tga_rgba "/MENU/dialog512_512.tga"
convert_tga_rgba "/MENU/dialog768_600.tga"
convert_tga_rgba "/MENU/panel444_333_back.tga"
convert_tga_rgba "/MENU/panel444_333_border.tga"
convert_tga_rgba "/MENU/panel800_444_back.tga"
convert_tga_rgba "/MENU/button_dialog200_out.tga"
convert_tga_rgba "/MENU/button_dialog200_in.tga"
convert_tga_rgba "/MENU/button_dialog200_off.tga"
convert_tga_rgba "/MENU/button_dialog128_out.tga"
convert_tga_rgba "/MENU/button_dialog128_in.tga"
convert_tga_rgba "/MENU/button_dialog128_off.tga"
convert_tga_rgba "/MENU/arrows_blue.tga"
convert_tga_rgba "/MENU/arrow_list_up.tga"
convert_tga_rgba "/MENU/arrow_list_down.tga"
convert_tga_rgba "/MENU/system_engine1.tga"
convert_tga_rgba "/MENU/system_engine2.tga"
convert_tga_rgba "/MENU/system_engine3.tga"
convert_tga_rgba "/MENU/system_engine4.tga"
convert_tga_rgba "/MENU/system_mechan1.tga"
convert_tga_rgba "/MENU/system_mechan2.tga"
convert_tga_rgba "/MENU/system_mechan3.tga"
convert_tga_rgba "/MENU/system_mechan4.tga"
convert_tga_rgba "/MENU/system_power1.tga"
convert_tga_rgba "/MENU/system_power2.tga"
convert_tga_rgba "/MENU/system_power3.tga"
convert_tga_rgba "/MENU/system_power4.tga"
convert_tga_rgba "/MENU/system_protect1.tga"
convert_tga_rgba "/MENU/system_protect2.tga"
convert_tga_rgba "/MENU/system_protect3.tga"
convert_tga_rgba "/MENU/system_protect4.tga"
convert_tga_rgba "/MENU/system_target1.tga"
convert_tga_rgba "/MENU/system_target2.tga"
convert_tga_rgba "/MENU/system_target3.tga"
convert_tga_rgba "/MENU/system_target4.tga"
convert_tga_rgba "/MENU/system_empty.tga"
convert_tga_rgba "/MENU/weapon1_icon.tga"
convert_tga_rgba "/MENU/weapon2_icon.tga"
convert_tga_rgba "/MENU/weapon3_icon.tga"
convert_tga_rgba "/MENU/weapon4_icon.tga"
convert_tga_rgba "/MENU/weapon5_icon.tga"
convert_tga_rgba "/MENU/weapon6_icon.tga"
convert_tga_rgba "/MENU/weapon7_icon.tga"
convert_tga_rgba "/MENU/weapon8_icon.tga"
convert_tga_rgba "/MENU/weapon9_icon.tga"
convert_tga_rgba "/MENU/weapon10_icon.tga"
convert_tga_rgba "/MENU/weapon11_icon.tga"
convert_tga_rgba "/MENU/weapon12_icon.tga"
convert_tga_rgba "/MENU/weapon13_icon.tga"
convert_tga_rgba "/MENU/weapon14_icon.tga"
convert_tga_rgba "/MENU/weapon15_icon.tga"
convert_tga_rgba "/MENU/weapon16_icon.tga"
convert_tga_rgba "/MENU/weapon17_icon.tga"
convert_tga_rgba "/MENU/weapon18_icon.tga"
convert_tga_rgba "/MENU/weapon19_icon.tga"
convert_tga_rgba "/MENU/weapon_on_icon.tga"
convert_tga_rgba "/MENU/weapon_empty_icon.tga"
convert_tga_rgba "/MENU/cursor.tga"
convert_tga_rgba "/MENU/cursor_shadow.tga"
convert_vw2d "/MODELS/EARTHFIGHTER/sf-text00.VW2D"
convert_vw2d "/MODELS/EARTHFIGHTER/sf-text05.VW2D"
convert_vw2d "/MODELS/EARTHFIGHTER/sf-text06.VW2D"
convert_vw2d "/MODELS/EARTHFIGHTER/sf-text07.VW2D"
convert_vw2d "/MODELS/EARTHFIGHTER/sf-text08.VW2D"
convert_vw2d "/MODELS/EARTHFIGHTER/sf-text09.VW2D"
convert_vw2d "/MODELS/EARTHFIGHTER/sf-text04.VW2D"
convert_vw2d "/MODELS/EARTHFIGHTER/sf-text10.VW2D"
convert_vw2d "/MODELS/EARTHFIGHTER/sf-illum01.VW2D"
convert_vw2d "/MODELS/EARTHFIGHTER/sf-illum02.VW2D"
convert_vw2d "/MODELS/EARTHFIGHTER/sf-illum03.VW2D"
convert_vw2d "/MODELS/EARTHFIGHTER/sf-illum04.VW2D"
convert_tga_rgb "/MODELS/EARTHFIGHTER/lnch12.tga"
convert_tga_rgb "/MODELS/EARTHFIGHTER/lnch34.tga"
convert_tga_rgb "/MODELS/EARTHFIGHTER/rockets.tga"
convert_vw2d "/MODELS/ALIENFIGHTER/al-text04.VW2D"
convert_vw2d "/MODELS/ALIENFIGHTER/al-illum04.VW2D"
convert_tga_minimal "/MODELS/SPACE/asteroid-01.tga"
convert_tga_rgba "/MODELS/PLANET/asteroid.tga"
convert_tga_rgba "/MODELS/PLANET/clouds.tga"
convert_tga_rgb "/MODELS/PLANET/q_class2.tga"
convert_tga_rgb "/MODELS/PLANET/a_class4.tga"
convert_tga_rgb "/MODELS/PLANET/m_class7.tga"
convert_tga_rgb "/MODELS/PLANET/d_class3.tga"
convert_tga_rgb "/MODELS/NORMALMAP/m_class7_nm.tga"
convert_tga_rgb "/MODELS/NORMALMAP/d_class3_nm.tga"
convert_tga_rgb "/MODELS/NORMALMAP/a_class4_nm.tga"
convert_tga_rgb "/MODELS/NORMALMAP/planet_asteroids_nm.tga"
convert_tga_rgb "/MODELS/NORMALMAP/q_class2_nm.tga"
convert_vw2d "/MODELS/gr-01.VW2D"
convert_vw2d "/MODELS/gr-02.VW2D"
convert_vw2d "/MODELS/gr-03.VW2D"
convert_vw2d "/MODELS/gr-04.VW2D"
convert_tga_rgb "/MODELS/NORMALMAP/bomber_nm.tga"
convert_vw2d "/MODELS/gr-05.VW2D"
convert_vw2d "/MODELS/gr-06.VW2D"
convert_vw2d "/MODELS/gr-07.VW2D"
convert_vw2d "/MODELS/track.VW2D"
convert_vw2d "/MODELS/ALIENMOTHERSHIP/alm-text02.VW2D"
convert_vw2d "/MODELS/ALIENMOTHERSHIP/alm-text03.VW2D"
convert_vw2d "/MODELS/ALIENMOTHERSHIP/alm-text04.VW2D"
convert_vw2d "/MODELS/ALIENMOTHERSHIP/alm-text08.VW2D"
convert_vw2d "/MODELS/ALIENMOTHERSHIP/alm-illum02.VW2D"
convert_vw2d "/MODELS/ALIENMOTHERSHIP/alm-illum03.VW2D"
convert_vw2d "/MODELS/ALIENMOTHERSHIP/alm-illum04.VW2D"
convert_vw2d "/MODELS/ALIENMOTHERSHIP/alm-illum08.VW2D"
convert_tga_rgb "/MODELS/NORMALMAP/alien_mothership_nm.tga"
convert_tga_rgb "/MODELS/TURRET/turrets.tga"
convert_vw2d "/MODELS/BUILDING/bld.VW2D"
convert_tga_rgb "/MODELS/NORMALMAP/buildings_nm.tga"
convert_vw2d "/MODELS/BUILDING/bld_illum.VW2D"
convert_tga_rgba "/MODELS/SPACEBASE/allalpha.tga"
convert_tga_rgb "/MODELS/SPACEBASE/metal.tga"
convert_tga_rgb "/MODELS/MINE/mine1.tga"
convert_tga_rgb "/MODELS/MINE/mine1i.tga"
convert_tga_rgb "/MODELS/MINE/mine2.tga"
convert_tga_rgb "/MODELS/MINE/mine2i.tga"
convert_tga_rgb "/MODELS/MINE/mine3.tga"
convert_tga_rgb "/MODELS/MINE/mine3i.tga"
convert_tga_rgb "/MODELS/MINE/mine4.tga"
convert_tga_rgb "/MODELS/MINE/mine4i.tga"
convert_tga_rgb "/SCRIPT/mission1_icon.tga"
convert_tga_rgb "/SCRIPT/mission2_icon.tga"
convert_tga_rgb "/SCRIPT/mission3_icon.tga"
convert_tga_rgb "/SCRIPT/mission4_icon.tga"
convert_tga_rgb "/SCRIPT/mission5_icon.tga"
convert_tga_rgb "/SCRIPT/mission6_icon.tga"
convert_tga_rgb "/SCRIPT/mission7_icon.tga"
convert_tga_rgb "/SCRIPT/mission8_icon.tga"
convert_tga_rgb "/SCRIPT/mission9_icon.tga"
convert_tga_rgb "/SCRIPT/mission10_icon.tga"
convert_tga_rgb "/SCRIPT/mission11_icon.tga"
convert_tga_rgb "/SCRIPT/mission12_icon.tga"
convert_tga_rgb "/SCRIPT/mission13_icon.tga"
convert_tga_rgb "/SCRIPT/mission14_icon.tga"
convert_tga_rgb "/SCRIPT/mission15_icon.tga"
convert_tga_rgb "/SKYBOX/1/skybox_bottom4.tga"
convert_tga_rgb "/SKYBOX/1/skybox_front5.tga"
convert_tga_rgb "/SKYBOX/1/skybox_back6.tga"
convert_tga_rgb "/SKYBOX/1/skybox_left2.tga"
convert_tga_rgb "/SKYBOX/1/skybox_right1.tga"
convert_tga_rgb "/SKYBOX/1/skybox_top3.tga"
convert_tga_rgb "/SKYBOX/2/skybox_back6.tga"
convert_tga_rgb "/SKYBOX/2/skybox_bottom4.tga"
convert_tga_rgb "/SKYBOX/2/skybox_front5.tga"
convert_tga_rgb "/SKYBOX/2/skybox_left2.tga"
convert_tga_rgb "/SKYBOX/2/skybox_right1.tga"
convert_tga_rgb "/SKYBOX/2/skybox_top3.tga"
convert_tga_rgb "/SKYBOX/tile_back.tga"
convert_tga_rgb "/SKYBOX/tile_stars.tga"
convert_ogg_wav "/MUSIC/menu.ogg"
convert_ogg_wav "/MUSIC/intro.ogg"
convert_ogg_wav "/MUSIC/game.ogg"
convert_ogg_wav "/MUSIC/boss-loop.ogg"
convert_ogg_wav "/MUSIC/missionfailed.ogg"
convert_ogg_wav "/MUSIC/boss-intro.ogg"
