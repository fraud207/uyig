#include "cmenu.hpp"
#include "..\cheats\misc\logs.h"

#include <shlobj.h>
#include <shlwapi.h>
struct hud_weapons_t
{
	std::int32_t* get_weapon_count()
	{
		return reinterpret_cast<std::int32_t*>(std::uintptr_t(this) + 0x80);
	}
};
template<class T>
static T* FindHudElement(const char* name)
{
	static auto pThis = *reinterpret_cast<DWORD**>(util::FindSignature("client_panorama.dll", "B9 ? ? ? ? E8 ? ? ? ? 8B 5D 08") + 1);

	static auto find_hud_element = reinterpret_cast<DWORD(__thiscall*)(void*, const char*)>(util::FindSignature("client_panorama.dll", "55 8B EC 53 8B 5D 08 56 57 8B F9 33 F6 39 77 28"));
	return (T*)find_hud_element(pThis, name);
}
void KnifeApplyCallbk()
{
	static auto clear_hud_weapon_icon_fn = reinterpret_cast<std::int32_t(__thiscall*)(void*, std::int32_t)>(util::FindSignature("client_panorama.dll", "55 8B EC 51 53 56 8B 75 08 8B D9 57 6B FE 2C"));

	auto element = FindHudElement<std::uintptr_t*>("CCSGO_HudWeaponSelection");

	auto hud_weapons = reinterpret_cast<hud_weapons_t*>(std::uintptr_t(element) - 0xA0);

	if (hud_weapons == nullptr)
		return;

	if (!*hud_weapons->get_weapon_count())
		return;

	for (std::int32_t i = 0; i < *hud_weapons->get_weapon_count(); i++)
		i = clear_hud_weapon_icon_fn(hud_weapons, i);

	typedef void(*ForceUpdate) (void);
	ForceUpdate FullUpdate = (ForceUpdate)util::FindSignaturenew("engine.dll", "FullUpdate", "A1 ? ? ? ? B9 ? ? ? ? 56 FF 50 14 8B 34 85");
	FullUpdate();
}

ConVar * Meme = nullptr;
void SkinApplyCallbk()
{
	if (!Meme) {
		static ConVar* Meme = g_csgo.m_cvar()->FindVar(("cl_fullupdate"));
		Meme->m_nFlags &= ~FCVAR_CHEAT;
		g_csgo.m_engine()->ClientCmd_Unrestricted("cl_fullupdate");
	}
}
std::string get_config_dir() {
	std::string folder;
	static TCHAR path[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, 0, path))) {
		folder = std::string(path) + "\\fluxware.win\\";
	}

	CreateDirectory(folder.c_str(), NULL);

	return folder;
}

void load_config() {
	if (!cfg_manager->files.size()) {
		return;
	}

	eventlogs::get().add("loaded " + cfg_manager->files[g_cfg.selected_config], Color::White);

	cfg_manager->load(cfg_manager->files[g_cfg.selected_config]);
}

void save_config() {
	if (!cfg_manager->files.size()) {
		return;
	}

	eventlogs::get().add("saved " + cfg_manager->files[g_cfg.selected_config], Color::White);

	cfg_manager->save(cfg_manager->files[g_cfg.selected_config]);
	cfg_manager->config_files();
}

void remove_config() {
	if (!cfg_manager->files.size()) {
		return;
	}

	cfg_manager->remove(cfg_manager->files[g_cfg.selected_config]);
	cfg_manager->config_files();

	if (g_cfg.selected_config > cfg_manager->files.size() - 1) {
		g_cfg.selected_config = cfg_manager->files.size() - 1;
	}
}

void add_config() {
	if (g_cfg.new_config_name.find(".cfg") == -1)
		g_cfg.new_config_name += ".cfg";

	cfg_manager->save(g_cfg.new_config_name.c_str());
	cfg_manager->config_files();

	g_cfg.new_config_name = "";

	g_cfg.selected_config = cfg_manager->files.size() - 1;
}

void unload_cheat() {
	unload = true;
}

std::vector<std::string> KnifeModel = { "Default",
"Bayonet",
"Flip Knife",
"Gut Knife",
"Karambit",
"M9 Bayonet",
"Huntsman Knife",
"Butterfly Knife",
"Falchion Knife",
"Shadow Daggers",
"Bowie Knife",
"Navaja Knife",
"Stiletto Knife",
"Ursus Knife",
"Talon Knife" };
std::vector<std::string> M4A4 = { "none",
"Asiimov",
"Howl",
"Dragon King",
"Poseidon",
"Daybreak",
"Royal Paladin",
"BattleStar",
"Desolate Space",
"Buzz Kill",
"Bullet Rain",
"Hell Fire",
"Evil Daimyo",
"Griffin",
"Zirka",
"Radiation Harzard", };
std::vector<std::string> knifeskins = { "none",
"Crimson Web",
"Bone Mask",
"Fade",
"Night",
"Blue Steel",
"Stained",
"Case Hardened",
"Slaughter",
"Safari Mesh",
"Boreal Forest",
"Ultraviolet",
"Urban Masked",
"Scorched",
"Rust Coat",
"Tiger Tooth",
"Damascus Steel",
"Damascus Steel",
"Marble Fade",
"Rust Coat",
"Doppler Ruby",
"Doppler Sapphire",
"Doppler Blackpearl",
"Doppler Phase 1",
"Doppler Phase 2",
"Doppler Phase 3",
"Doppler Phase 4",
"Doppler Phase 4",
"Gamma Doppler Phase 1",
"Gamma Doppler Phase 2",
"Gamma Doppler Phase 3",
"Gamma Doppler Phase 4",
"Gamma Doppler Emerald",
"Lore",
"Black Laminate",
"Autotronic",
"Freehand" };
std::vector<std::string> ak47 = { "none",
"Fire Serpent",
"Fuel Injector",
"Bloodsport",
"Vulcan",
"Case Hardened",
"Hydroponic",
"Aquamarine Revenge",
"Frontside Misty",
"Point Disarray",
"Neon Revolution",
"Red Laminate",
"Redline",
"Jaguar",
"Jet Set",
"Wasteland Rebel",
"The Empress",
"Elite Build",
"Neon Rider" };
std::vector<std::string> GloveModel = { "none",
"Bloodhound",
"Sport",
"Driver",
"Wraps",
"Moto",
"Specialist" };

std::vector<std::string> Duals = { "none",
"Panther",
"Dualing Dragons",
"Cobra Strike",
"Royal Consorts",
"Duelist" };
std::vector<std::string> M4A1 = { "none",
"Decimator",
"Knight",
"Chantico's Fire",
"Golden Coi",
"Hyper Beast",
"Master Piece",
"Hot Rod",
"Mecha Industries",
"Cyrex",
"Icarus Fell",
"Flashback",
"Flashback",
"Hyper Beast",
"Atomic Alloy",
"Guardian",
"Briefing" };
std::vector<std::string> Usp = { "none",
"Neo-Noir",
"Cyrex",
"Orion",
"Kill Confirmed",
"Overgrowth",
"Caiman",
"Serum",
"Guardian",
"Road Rash" };
std::vector<std::string> Glock = { "none",
"Fade",
"Dragon Tattoo",
"Twilight Galaxy",
"Wasteland Rebel",
"Water Elemental",
"Off World",
"Weasel",
"Royal Legion",
"Grinder",
"Steel Disruption",
"Brass",
"Ironwork",
"Bunsen Burner",
"Reactor" };
std::vector<std::string> Deagle = { "none",
"Blaze",
"Kumicho Dragon",
"Oxide Blaze",
"Golden Koi",
"Cobalt Disruption",
"Directive" };
std::vector<std::string> Five7 = { "none",
"Monkey Business",
"Hyper Beast",
"Fowl Play",
"Triumvirate",
"Retrobution",
"Capillary",
"Violent Daimyo" };
std::vector<std::string> Aug = { "none",
"Bengal Tiger",
"Hot Rod",
"Chameleon",
"Akihabara Accept" };
std::vector<std::string> Famas = { "none",
"Djinn",
"Styx",
"Neural Net",
"Survivor Z" };
std::vector<std::string> G3sg1Skin = { "none",
"Hunter",
"The Executioner",
"Terrace" };
std::vector<std::string> Galil = { "none",
"Chatterbox",
"Crimson Tsunami",
"Sugar Rush",
"Eco",
"Cerberus" };
std::vector<std::string> M249 = { "none",
"Nebula Crusader",
"System Lock",
"Magma" };
std::vector<std::string> Mac10 = { "none",
"Neon Rider",
"Last Dive",
"Curse",
"Rangeen",
"Rangeen" };
std::vector<std::string> Ump45 = { "none",
"Blaze",
"Minotaur's Labyrinth",
"Pandora's Box",
"Primal Saber",
"Exposure" };
std::vector<std::string> XM1014 = { "none",
"Seasons",
"Traveler",
"Ziggy" };
std::vector<std::string> Cz75 = { "none",
"Red Astor",
"Pole Position",
"Victoria",
"Xiangliu" };
std::vector<std::string> PPBizon = { "none",
"High Roller",
"Judgement of Anubis",
"Fuel Rod" };
std::vector<std::string> Mag7 = { "none",
"Bulldozer",
"Heat",
"Petroglyph" };
std::vector<std::string> Awpskinse = { "none",
"Asiimov",
"Dragon Lore",
"Fever Dream",
"Medusa",
"HyperBeast",
"Boom",
"Lightning Strike",
"Pink DDpat",
"Corticera",
"Redline",
"Manowar",
"Graphite",
"Electric Hive",
"Sun in Leo",
"Hyper Beast",
"Pit viper",
"Phobos",
"Elite Build",
"Worm God",
"Oni Taiji",
"Fever Dream" };
std::vector<std::string> negev = { "none",
"Power Loader",
"Loudmouth",
"Man-o'-war" };
std::vector<std::string> Sawedoff = { "none",
"Wasteland Princess",
"The Kraken",
"Yorick" };
std::vector<std::string> tec9 = { "none",
"Nuclear Threat",
"Red Quartz",
"Blue Titanium",
"Titanium Bit",
"Sandstorm",
"Isaac",
"Toxic",
"Re-Entry",
"Fuel Injector" };
std::vector<std::string> P2000 = { "none",
"Handgun",
"Fade",
"Corticera",
"Ocean Foam",
"Fire Elemental",
"Asterion",
"Pathfinder",
"Imperial",
"Oceanic",
"Imperial Dragon" };
std::vector<std::string> Mp7 = { "none",
"Nemesis",
"Impire",
"Special Delivery" };
std::vector<std::string> Mp9 = { "none",
"Rose Iron",
"Ruby Poison Dart",
"Airlock" };
std::vector<std::string> Nova = { "none",
"Hyper Beast",
"Koi",
"Antique" };
std::vector<std::string> P250 = { "none",
"Whiteout",
"Crimson Kimono",
"Mint Kimono",
"Wingshot",
"Asiimov",
"See Ya Later" };
std::vector<std::string> SCAR20 = { "none",
"Splash Jam",
"Storm",
"Contractor",
"Carbon Fiber",
"Sand Mesh",
"Palm",
"Crimson Web",
"Cardiac",
"Army Sheen",
"Cyrex",
"Grotto",
"Bloodsport" };
std::vector<std::string> Sg553 = { "none",
"Tiger Moth",
"Cyrex",
"Pulse",
"Fallout Warning" };
std::vector<std::string> SSG08 = { "none",
"Lichen Dashed",
"Dark Water",
"Blue Spruce",
"Sand Dune",
"Palm",
"Mayan Dreams",
"Blood in the Water",
"Tropical Storm",
"Acid Fade",
"Slashed",
"Detour",
"Abyss",
"Big Iron",
"Necropos",
"Ghost Crusader",
"Dragonfire" };
std::vector<std::string> Revolver = { "none",
"Llama Cannon",
"Fade",
"Crimson Web", };

void setup_main_menu() {
	static auto set_sub = [](int sub) -> void {
		g_cfg.menu.group_sub = sub;
	};

	static auto set_tabsub = [](int sub) -> void {
		g_cfg.menu.tab_sub = sub;
	};

	auto rage_tab = new C_Tab(&menu::get(), 1, "", "aimbot", {
		C_Tab::subtab_t("v", 0, fonts[SUBTABWEAPONS]),
		C_Tab::subtab_t("E", 1, fonts[SUBTABWEAPONS]),
		C_Tab::subtab_t("A", 2, fonts[SUBTABWEAPONS]),
		C_Tab::subtab_t("W", 3, fonts[SUBTABWEAPONS]),
		C_Tab::subtab_t("O", 4, fonts[SUBTABWEAPONS]),
		C_Tab::subtab_t("a", 5, fonts[SUBTABWEAPONS]),
		C_Tab::subtab_t("Y", 6, fonts[SUBTABWEAPONS]),
		C_Tab::subtab_t("e", 7, fonts[SUBTABWEAPONS])
		}); {
		set_tabsub(0);

		auto rage = new C_GroupBox(GROUP_LEFT, 8, ""); {
			auto enable = new C_CheckBox("enable", &g_cfg.ragebot.enable);

			auto fov = new C_SliderInt("field of view", &g_cfg.ragebot.field_of_view, 0, 360, "°");

			auto selection_type = new C_Dropdown("selection type", &g_cfg.ragebot.selection_type, { "field of view", "distance", "health" });

			auto silent_aim = new C_CheckBox("silent aim", &g_cfg.ragebot.silent_aim);

			auto anti_recoil = new C_CheckBox("anti recoil", &g_cfg.ragebot.anti_recoil);

			auto anti_spread = new C_CheckBox("anti spread", &g_cfg.ragebot.anti_spread);

			auto zeus_bot = new C_CheckBox("zeus bot", &g_cfg.ragebot.zeus_bot);
			auto auto_pistols = new C_CheckBox("auto pistols", &g_cfg.ragebot.auto_pistols);
			auto auto_revolver = new C_CheckBox("auto revolver", &g_cfg.ragebot.auto_revolver);
			auto extrapolation = new C_CheckBox("extrapolation", &g_cfg.ragebot.extrapolation);
		}

		auto rage2 = new C_GroupBox(GROUP_RIGHT, 8, ""); {
			auto aa_correction = new C_CheckBox("anti-aim correction", &g_cfg.ragebot.antiaim_correction);

			auto desync_fix = new C_CheckBox("desync fix", &g_cfg.ragebot.desync_fix);
			auto override_key = new C_KeyBind("override key", &g_cfg.ragebot.override_key);

			auto aimstep = new C_CheckBox("aim step", &g_cfg.ragebot.aimstep);

			auto lagcomp = new C_CheckBox("lag compensation", &g_cfg.ragebot.lagcomp);

			auto lagcomp_time = new C_SliderFloat("", &g_cfg.ragebot.lagcomp_time, 0, 0.20, "s");

			auto lag_compensation_type = new C_Dropdown("compensation type", &g_cfg.ragebot.lag_compensation_type, { "refine shot", "prediction" });
		}

		for (int i = 0; i < 7; i++) {
			set_tabsub(i + 1);

			auto weapon = new C_GroupBox(GROUP_LEFT, 8, ""); {
				auto autoshoot = new C_CheckBox("autoshoot", &g_cfg.ragebot.autoshoot[i]);
				auto autowall = new C_CheckBox("autowall", &g_cfg.ragebot.autowall[i]);
				auto minimum_damage = new C_SliderInt("", &g_cfg.ragebot.minimum_damage[i], 1, 100, "");

				if (i == 2 || i == 4 || i == 5) {
					int autoscope_element;

					if (i == 2) autoscope_element = 0;
					if (i == 4) autoscope_element = 1;
					if (i == 5) autoscope_element = 2;

					auto autoscope = new C_CheckBox("autoscope", &g_cfg.ragebot.autoscope[autoscope_element]);
				}

				auto hitchance = new C_CheckBox("hitchance", &g_cfg.ragebot.hitchance[i]);
				auto hitchance_amount = new C_SliderInt("", &g_cfg.ragebot.hitchance_amount[i], 0, 100, "%");

				auto hitscan = new C_MultiDropdown("hitboxes", &g_cfg.ragebot.hitscan[i]);

				auto hitscan_history = new C_MultiDropdown("hitbox history", &g_cfg.ragebot.hitscan_history[i]);
				auto multipoint = new C_MultiDropdown("multipoint", &g_cfg.ragebot.multipoint_hitboxes[i]);
				auto pointscale = new C_SliderFloat("pointscale", &g_cfg.ragebot.pointscale[i], 0, 1, "");
			}

			auto weapon2 = new C_GroupBox(GROUP_RIGHT, 8, ""); {
				auto baim = new C_MultiDropdown("baim", &g_cfg.ragebot.baim_settings[i]);

				auto baim_hp = new C_SliderInt("baim health", &g_cfg.ragebot.baim_health[i], 0, 100, "hp");
				auto baim_key = new C_KeyBind("baim key", &g_cfg.ragebot.baim_key);
			   // auto baimshotenable = new C_CheckBox("baimshotenable", &g_cfg.ragebot.baimshotenable);
				//auto baimshotenableslider = new C_SliderInt("", &g_cfg.ragebot.baimshotenableslider, 0, 10, "");
				auto quickstop = new C_CheckBox("quickstop", &g_cfg.ragebot.quickstop[i]);
				auto quickstop_type = new C_Dropdown("", &g_cfg.ragebot.quickstoptype, { "defaut", "agresive" });
			}
		}
	}

	auto antiaim_tab = new C_Tab(&menu::get(), 2, "", "antiaim", {
		C_Tab::subtab_t("stand", 1, fonts[TAHOMA12]),
		C_Tab::subtab_t("move", 2, fonts[TAHOMA12]),
		C_Tab::subtab_t("air", 3, fonts[TAHOMA12]),
		}); {
		set_tabsub(0);

		for (int i = 0; i < 3; i++) {
			set_tabsub(i + 1);

			auto antiaim = new C_GroupBox(GROUP_LEFT, 8, ""); {

				auto base_angle = new C_Dropdown("base angle", &g_cfg.antiaim.base_angle[i], { "static", "crosshair", "at targets" });

				auto pitch = new C_Dropdown("pitch", &g_cfg.antiaim.pitch[i], { "off", "down", "up", "minimal", "fake zero", "fake down", "fake up" });

				std::vector< std::string > reals{ "off", "sideways", "backwards", "rotate", "jitter", "local view", "lowerbody", "desync+freestanding","goodfreestanding", };

				auto yaw = new C_Dropdown("yaw", &g_cfg.antiaim.yaw[i], reals);
				auto yaw_offset = new C_SliderInt("", &g_cfg.antiaim.yaw_offset[i], -180, 180, "°");

				std::vector< std::string > fakes{ "off", "use!" };

				auto DESYNCANTIAIM2 = new C_CheckBox("DesyncJitter without Key", &g_cfg.antiaim.DESYNCANTIAIM2);
				auto DESYNCANTIAIM = new C_KeyBind("DesyncJitter With key", &g_cfg.antiaim.DESYNCANTIAIM);


				auto lby_breaker = new C_CheckBox("break lby", &g_cfg.antiaim.lby_breaker);
				auto lby_delta = new C_SliderInt("", &g_cfg.antiaim.lby_delta, -180, 180, "°");
				auto flick_up = new C_CheckBox("flick up", &g_cfg.antiaim.pitch_flick);
				auto balance_breaker = new C_CheckBox("balance breaker", &g_cfg.antiaim.break_adjustment);
			}

			auto antiaim_2 = new C_GroupBox(GROUP_RIGHT, 8, ""); {
				auto manualkey_left = new C_KeyBind("manual key left", &g_cfg.antiaim.left_manualkey);
				auto manualkey_right = new C_KeyBind("manual key right", &g_cfg.antiaim.right_manualkey);
				auto manualkey_back = new C_KeyBind("manual key back", &g_cfg.antiaim.back_manualkey);

				auto fakelag_enablers = new C_MultiDropdown("fakelag", &g_cfg.antiaim.fakelag_enablers);
				auto fakelag_mode = new C_Dropdown("", &g_cfg.antiaim.fakelag_mode, { "factor", "dynamic", "Maximum" });
				auto fakelag_amount = new C_SliderInt("", &g_cfg.antiaim.fakelag_amount, 1, 14, "");
				//	auto fakelag_onpeek = new C_CheckBox( "on peek *todo*", &g_cfg.antiaim.fakelag_onpeek );
				//	auto fakelag_onpeek_amt = new C_SliderInt( "", &g_cfg.antiaim.fakelag_onpeek_amt, 1, 14, "" );
			}
		}
	}
	

	auto player_tab = new C_Tab(&menu::get(), 3, "", "players"); {
		auto player = new C_GroupBox(GROUP_LEFT, 8, ""); {
			auto enable = new C_CheckBox("enable", &g_cfg.player.enable);

			auto alpha = new C_SliderInt("alpha", &g_cfg.player.alpha, 0, 255, "");

			auto pov_arrow = new C_CheckBox("enemy offscreen esp", &g_cfg.player.out_pov_arrow,
				{ new C_ColorSelector(&g_cfg.player.out_pov_arrow_color) });

			auto pov_distance = new C_SliderInt("", &g_cfg.player.out_pov_distance, 25, 400, "");

			auto box = new C_CheckBox("bounding box", &g_cfg.player.box,
				{ new C_ColorSelector(&g_cfg.player.box_color) });

			auto health = new C_CheckBox("health", &g_cfg.player.health);

			auto name = new C_CheckBox("name", &g_cfg.player.name,
				{ new C_ColorSelector(&g_cfg.player.name_color) });

			auto weapon = new C_CheckBox("weapon", &g_cfg.player.weapon,
				{ new C_ColorSelector(&g_cfg.player.weapon_color) });

			auto ammo = new C_Dropdown("ammunition", &g_cfg.player.ammo, { "off", "ammo bar" });

			auto ammobar_color = new C_TextSeperator("color bar", SEPERATOR_NORMAL,
				{ new C_ColorSelector(&g_cfg.player.ammobar_color) });


			auto flags = new C_MultiDropdown("flags", &g_cfg.player.flags);

			auto skeleton = new C_MultiDropdown("skeleton", &g_cfg.player.skeleton);
		}

		auto player_2 = new C_GroupBox(GROUP_RIGHT, 8, ""); {
			auto glow = new C_MultiDropdown("glow", &g_cfg.player.glow);

			auto glow_color_enemy = new C_TextSeperator("color enemy", SEPERATOR_NORMAL,
				{ new C_ColorSelector(&g_cfg.player.glow_color_enemy) });

			auto glow_color_teammate = new C_TextSeperator("color teammate", SEPERATOR_NORMAL,
				{ new C_ColorSelector(&g_cfg.player.glow_color_teammate) });

			auto glow_color_local= new C_TextSeperator("color local", SEPERATOR_NORMAL,
				{ new C_ColorSelector(&g_cfg.player.glow_color_local) });

			auto glow_opacity = new C_SliderInt("", &g_cfg.player.glowopacity, 1, 100, "%%");

			auto glow_bloom = new C_SliderInt("", &g_cfg.player.glowbloom, 1, 100, "%%");

			auto glow_type = new C_Dropdown("", &g_cfg.player.glow_type, { "outline outer", "cover", "outline inner" });

			auto chams = new C_MultiDropdown("chams", &g_cfg.player.chams);

			auto chams_color_visible = new C_TextSeperator("color visible", SEPERATOR_NORMAL,
				{ new C_ColorSelector(&g_cfg.player.chams_color) });

			auto chams_color_invisible = new C_TextSeperator("color invisible", SEPERATOR_NORMAL,
				{ new C_ColorSelector(&g_cfg.player.xqz_color) });

			auto chams_opacity = new C_SliderInt("", &g_cfg.player.chams_opacity, 0, 100, "%%");

			auto chams_type = new C_Dropdown("", &g_cfg.player.chams_type, { "regular", "flat", "rubber", "metallic" });

			auto backtrack_chams = new C_CheckBox("backtrack model", &g_cfg.player.backtrack_chams,
				{ new C_ColorSelector(&g_cfg.player.backtrack_chams_color) });

			auto backtrack_chams_opacity = new C_SliderInt("", &g_cfg.player.backtrack_chams_opacity, 0, 100, "%%");
		}

		auto esp_tab = new C_Tab(&menu::get(), 4, "", "other visuals"); {
			auto esp = new C_GroupBox(GROUP_LEFT, 8, ""); {
				auto fov = new C_SliderInt("override fov", &g_cfg.esp.fov, 0, 89, "°");
				auto viewmodel_x = new C_SliderInt("view model[x]", &g_cfg.esp.viewmodel_x, 0, 30, "°");
				auto viewmodel_y = new C_SliderInt("view model[y]", &g_cfg.esp.viewmodel_y, 0, 30, "°");
				auto viewmodel_z = new C_SliderInt("view model[z]", &g_cfg.esp.viewmodel_z, 0, 30, "°");
				auto override_fov_scoped = new C_CheckBox("override fov when scoped", &g_cfg.esp.override_fov_scoped);

				auto knifeleft = new C_CheckBox("knifeLeft", &g_cfg.esp.knifeleft);
				auto aspectratioenable = new C_CheckBox("fan aspect ratio", &g_cfg.esp.aspectratioenable);
				auto aspectratio = new C_SliderInt("range", &g_cfg.esp.aspectratio, 0, 199, "");


				auto show_spread = new C_CheckBox("show spread", &g_cfg.esp.show_spread,
					{ new C_ColorSelector(&g_cfg.esp.show_spread_color) });

				auto crosshair = new C_CheckBox("crosshair", &g_cfg.esp.crosshair);

				auto hands = new C_CheckBox("hands", &g_cfg.esp.hands,
				{ new C_ColorSelector(&g_cfg.esp.hands_color) });
				auto hands_alpha = new C_SliderInt("hands_alpha", &g_cfg.esp.hands_alpha, 0, 100, "%%");

				auto pulsation = new C_CheckBox("pulsation", &g_cfg.esp.pulsation);

				auto penetration_reticle = new C_CheckBox("penetration reticle", &g_cfg.esp.penetration_reticle);

				auto antiaim_indicator = new C_CheckBox("anti-aim indicator", &g_cfg.esp.antiaim_indicator);

				auto croked_indicator = new C_CheckBox("croked indicator", &g_cfg.esp.croked_indicator);
				auto extend_indicator = new C_CheckBox("extend indicator", &g_cfg.esp.extend_indicator);
				auto lc_indicator = new C_CheckBox("lc indicator", &g_cfg.esp.lc_indicator);

				auto ghost_chams = new C_CheckBox("ghost chams", &g_cfg.esp.ghost_chams,
					{ new C_ColorSelector(&g_cfg.esp.ghost_chams_color) });

				auto local_chams = new C_CheckBox("local chams", &g_cfg.esp.local_chams,
					{ new C_ColorSelector(&g_cfg.esp.local_chams_color) });

				auto local_chams_fakelag = new C_CheckBox("local chams fakelag", &g_cfg.esp.local_chams_fakelag,
					{ new C_ColorSelector(&g_cfg.esp.localfakelag_chams_color) });

				auto chams_opacitylocal1 = new C_SliderInt("opacity chams", &g_cfg.player.chams_opacitylocal1, 0, 50, "%%");
			}

			auto esp_2 = new C_GroupBox(GROUP_RIGHT, 8, ""); {
				auto dropped_weapon = new C_CheckBox("dropped weapon", &g_cfg.esp.dropped_weapons,
					{ new C_ColorSelector(&g_cfg.esp.dropped_weapons_color) });

				auto projectiles = new C_CheckBox("projectiles", &g_cfg.esp.projectiles,
					{ new C_ColorSelector(&g_cfg.esp.projectiles_color) });


				auto dont_render_teammates = new C_CheckBox("dont't render teammates", &g_cfg.esp.dont_render_teammates);

				auto spectators = new C_CheckBox("spectators", &g_cfg.esp.spectators);

				auto zeus_tanger = new C_CheckBox("zeus tanger\\crash", &g_cfg.esp.zeusrange,
					{ new C_ColorSelector(&g_cfg.esp.zeusrange_color) });

				auto damageindicator = new C_CheckBox("damageindicator", &g_cfg.esp.damageindicator);

				auto bombesp = new C_CheckBox("bombesp", &g_cfg.esp.bombesp);

				auto hitmarker = new C_MultiDropdown("hitmarker", &g_cfg.esp.hitmarker);

				auto hitsound = new C_CheckBox("hitsound", &g_cfg.esp.hitsound);

				auto removals = new C_MultiDropdown("removals", &g_cfg.esp.removals);

				auto bullet_tracer = new C_CheckBox("bullet tracers", &g_cfg.esp.bullet_tracer,
					{ new C_ColorSelector(&g_cfg.esp.bullet_tracer_color) });

				auto worldsupremacy = new C_MultiDropdown("world", &g_cfg.esp.worldsupremacy); // supremacy hi
				auto skybox = new C_Dropdown("sky box", &g_cfg.esp.skybox,
					{ "Tibet",
					"Baggage",
					"Monastery",
					"Italy/OldInferno",
					"Aztec",
					"Vertigo",
					"Daylight",
					"Daylight (2)",
					"Clouds",
					"Clouds (2)",
					"Gray",
					"Clear",
					"Canals",
					"Cobblestone",
					"Assault",
					"Clouds (Dark)",
					"Night",
					"Night (2)",
					"Night (Flat)",
					"Dusty",
					"Rainy",
					"Custom: Sunrise",
					"Custom: Galaxy",
					"Custom: Galaxy (2)",
					"Custom: Galaxy (3)",
					"Custom: Clouds (Night)",
					"Custom: Ocean",
					"Custom: Grimm Night",
					"Custom: Heaven",
					"Custom: Heaven (2)",
					"Custom: Clouds",
					"Custom: Night (Blue)" });
				auto ColorSkyr = new C_SliderInt("colorSkyr", &g_cfg.esp.ColorSkyr, 0, 25, "°");
				auto ColorSkyg = new C_SliderInt("colorSkyg", &g_cfg.esp.ColorSkyg, 0, 25, "°");
				auto ColorSkyb = new C_SliderInt("colorSkyb", &g_cfg.esp.ColorSkyb, 0, 25, "°");
			}
			auto watemark = new C_CheckBox("watemark sync", &g_cfg.esp.watemark);
		}
	}
	auto skins_tab = new C_Tab(&menu::get(), 5, "", "skins"); {
		auto skinchanger = new C_GroupBox(GROUP_LEFT, 8, ""); {

			auto knifechanger = new C_GroupBox(GROUP_LEFT, 12, "skin changer");
			{
				auto skinson = new C_CheckBox("enable Skinchanger", &g_cfg.skins.skinenabled);

			}
			auto knifechanger2 = new C_GroupBox(GROUP_RIGHT, 12, "knifeChanger");
			{
				//auto knifeshahaha = new C_CheckBox("Enable Knife Changer", &g_cfg.skins.knifes);
				auto knif = new C_Dropdown("knife Model", &g_cfg.skins.Knife, { "Bayonet",
					"Flip Knife",
					"Gut Knife",
					"Karambit",
					"M9 Bayonet",
					"Huntsman Knife",
					"Butterfly Knife",
					"Falchion Knife",
					"Shadow Daggers",
					"Bowie Knife",
					"Navaja Knife",
					"Stiletto Knife",
					"Ursus Knife",
					"Talon Knife" });

				auto knifskin = new C_Dropdown("knife Skin", &g_cfg.skins.KnifeSkin, { "none",
					"Crimson Web",
					"Bone Mask",
					"Fade",
					"Night",
					"Blue Steel",
					"Stained",
					"Case Hardened",
					"Slaughter",
					"Safari Mesh",
					"Boreal Forest",
					"Ultraviolet",
					"Urban Masked",
					"Scorched",
					"Rust Coat",
					"Tiger Tooth",
					"Damascus Steel",
					"Damascus Steel",
					"Marble Fade",
					"Rust Coat",
					"Doppler Ruby",
					"Doppler Sapphire",
					"Doppler Blackpearl",
					"Doppler Phase 1",
					"Doppler Phase 2",
					"Doppler Phase 3",
					"Doppler Phase 4",
					"Gamma Doppler Phase 1",
					"Gamma Doppler Phase 2",
					"Gamma Doppler Phase 3",
					"Gamma Doppler Phase 4",
					"Gamma Doppler Emerald",
					"Lore",
					"Black Laminate",
					"Autotronic",
					"Abuss", });
				auto forceupdate = new C_Button("full Update", []() { KnifeApplyCallbk(); });
				set_tabsub(1);
			}
		}
	}

	auto misc_tab = new C_Tab(&menu::get(), 6, "", "misc"); {
		auto miscellaneous = new C_GroupBox(GROUP_LEFT, 8, ""); {
			auto bunnyhop = new C_CheckBox("automatic jump", &g_cfg.misc.bunnyhop); 
			auto airstrafe = new C_CheckBox("automatic strafe", &g_cfg.misc.airstrafe);
			auto circle_stafer = new C_KeyBind("circle strafe", &g_cfg.misc.circle_strafe);
			auto thirdperson = new C_KeyBind("thirdperson", &g_cfg.misc.thirdperson_toggle);
			auto events_to_log = new C_MultiDropdown("activity log", &g_cfg.misc.events_to_log);
			auto sniper_crosshair = new C_CheckBox("sniper crosshair", &g_cfg.misc.sniper_crosshair);
		}

		auto miscellaneous_2 = new C_GroupBox(GROUP_RIGHT, 8, ""); {
			auto exaggerated_ragdoll = new C_CheckBox("exaggerated ragdolls", &g_cfg.misc.exaggerated_ragdolls);
			auto ping_spike = new C_CheckBox("fake latency", &g_cfg.misc.ping_spike);
			auto ping_spike_value = new C_SliderInt("", &g_cfg.misc.ping_spike_value, 0, 200, "ms");
			auto fakewalk = new C_CheckBox("slow walk", &g_cfg.misc.fakewalk);
			auto fakewalk_key = new C_KeyBind("", &g_cfg.misc.fakewalk_key);
			auto fakeduck = new C_KeyBind("fake duck", &g_cfg.misc.fakeduck);
			auto no_crouch_cooldown = new C_CheckBox("instant unduck", &g_cfg.misc.no_crouch_cooldown);
			auto presentkiller = new C_CheckBox("preverse killfeed", &g_cfg.misc.preversekillfeed);
			// Buybot
			auto buybot_enable = new C_CheckBox("buybot", &g_cfg.misc.buybot_enable); // Yeah, just a checkbox

			auto buybot_rifleschoice = new C_Dropdown("", &g_cfg.misc.buybot_rifleschoice, { "None", "Auto", "Scout", "AWP", "AK/M4", "AUG/SG" }); // Creates Combobox
			auto buybot_pistolchoice = new C_Dropdown("", &g_cfg.misc.buybot_pistolchoice, { "None", "Elites", "DEAG/R8", "P250" }); // Creates Combobox
			auto buybot_extras = new C_MultiDropdown("extras", &g_cfg.misc.buybot_extras); // Creates multibox :)
		}
	}

	auto configs_tab = new C_Tab(&menu::get(), 7, "", "config"); {
		auto config = new C_GroupBox(GROUP_LEFT, 8, ""); {
			auto menu_color = new C_TextSeperator("menu color", SEPERATOR_NORMAL,
				{ new C_ColorSelector(&g_cfg.menu.menu_theme[0]) });

			auto menu_bind = new C_KeyBind("menu bind", &g_cfg.menu.menu_bind);

			auto anti_untrusted = new C_CheckBox("anti-unstrusted", &g_cfg.misc.anti_untrusted);
			auto clantag = new C_CheckBox("clantag - FluxWare", &g_cfg.misc.clantag_spammer);
		}

		auto config_2 = new C_GroupBox(GROUP_RIGHT, 8, ""); {
			auto config_dropdown = new C_Dropdown("", &g_cfg.selected_config, &cfg_manager->files);

			auto function_seperator = new C_TextSeperator("functions", SEPERATOR_BOLD);

			auto load = new C_Button("load", []() { load_config(); });
			auto save = new C_Button("save", []() { save_config(); });
			auto remove = new C_Button("remove", []() { remove_config(); });
			new C_TextField("config name", &g_cfg.new_config_name);
			auto add = new C_Button("add", []() { add_config(); });
			new C_Button("unload cheat", []() { unload_cheat(); });
		}
	}
}
