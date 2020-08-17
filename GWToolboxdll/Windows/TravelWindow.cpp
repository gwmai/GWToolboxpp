#include "stdafx.h"

#include <GWCA/Constants/Constants.h>

#include <GWCA/Packets/StoC.h>
#include <GWCA/Managers/StoCMgr.h>

#include <GWCA/GameContainers/GamePos.h>

#include <GWCA/GameEntities/Guild.h>
#include <GWCA/GameEntities/Map.h>
#include <GWCA/GameEntities/Party.h>

#include <GWCA/Context/GameContext.h>
#include <GWCA/Context/WorldContext.h>
#include <GWCA/Context/PartyContext.h>
#include <GWCA/Context/GuildContext.h>

#include <GWCA/Managers/MapMgr.h>
#include <GWCA/Managers/GuildMgr.h>
#include <GWCA/Managers/PartyMgr.h>
#include <GWCA/Managers/ChatMgr.h>
#include <GWCA/Managers/ItemMgr.h>
#include <GWCA/Managers/GameThreadMgr.h>
#include <GWCA/Managers/UIMgr.h>

#include <GuiUtils.h>
#include <GWToolbox.h>

#include <Modules/Resources.h>
#include <Windows/TravelWindow.h>

#define N_OUTPOSTS 180
#define N_DISTRICTS 14

namespace {
    bool outpost_name_array_getter(void* data, int idx, const char** out_text);

    bool ImInPresearing() { return GW::Map::GetCurrentMapInfo()->region == GW::Region_Presearing; }

    bool outpost_name_array_getter(void *data, int idx, const char **out_text)
    {
        UNREFERENCED_PARAMETER(data);
        switch (idx) {
            case 0:
                *out_text = "Abaddon's Gate";
                break;
            case 1:
                *out_text = "Abaddon's Mouth";
                break;
            case 2:
                *out_text = "Altrumm Ruins";
                break;
            case 3:
                *out_text = "Amatz Basin";
                break;
            case 4:
                *out_text = "Amnoon Oasis, The";
                break;
            case 5:
                *out_text = "Arborstone";
                break;
            case 6:
                *out_text = "Ascalon City";
                break;
            case 7:
                *out_text = "Aspenwood Gate (Kurzick)";
                break;
            case 8:
                *out_text = "Aspenwood Gate (Luxon)";
                break;
            case 9:
                *out_text = "Astralarium, The";
                break;
            case 10:
                *out_text = "Augury Rock";
                break;
            case 11:
                *out_text = "Aurios Mines, The";
                break;
            case 12:
                *out_text = "Aurora Glade";
                break;
            case 13:
                *out_text = "Bai Paasu Reach";
                break;
            case 14:
                *out_text = "Basalt Grotto";
                break;
            case 15:
                *out_text = "Beacon's Perch";
                break;
            case 16:
                *out_text = "Beetletun";
                break;
            case 17:
                *out_text = "Beknur Harbor";
                break;
            case 18:
                *out_text = "Bergen Hot Springs";
                break;
            case 19:
                *out_text = "Blacktide Den";
                break;
            case 20:
                *out_text = "Bloodstone Fen";
                break;
            case 21:
                *out_text = "Bone Palace";
                break;
            case 22:
                *out_text = "Boreal Station";
                break;
            case 23:
                *out_text = "Boreas Seabed";
                break;
            case 24:
                *out_text = "Borlis Pass";
                break;
            case 25:
                *out_text = "Brauer Academy";
                break;
            case 26:
                *out_text = "Breaker Hollow";
                break;
            case 27:
                *out_text = "Camp Hojanu";
                break;
            case 28:
                *out_text = "Camp Rankor";
                break;
            case 29:
                *out_text = "Cavalon";
                break;
            case 30:
                *out_text = "Central Transfer Chamber";
                break;
            case 31:
                *out_text = "Chahbek Village";
                break;
            case 32:
                *out_text = "Champion's Dawn";
                break;
            case 33:
                *out_text = "Chantry of Secrets";
                break;
            case 34:
                *out_text = "Codex Arena";
                break;
            case 35:
                *out_text = "Consulate Docks";
                break;
            case 36:
                *out_text = "Copperhammer Mines";
                break;
            case 37:
                *out_text = "D'Alessio Seaboard";
                break;
            case 38:
                *out_text = "Dajkah Inlet";
                break;
            case 39:
                *out_text = "Dasha Vestibule";
                break;
            case 40:
                *out_text = "Deep, The";
                break;
            case 41:
                *out_text = "Deldrimor War Camp";
                break;
            case 42:
                *out_text = "Destiny's Gorge";
                break;
            case 43:
                *out_text = "Divinity Coast";
                break;
            case 44:
                *out_text = "Doomlore Shrine";
                break;
            case 45:
                *out_text = "Dragon's Lair, The";
                break;
            case 46:
                *out_text = "Dragon's Throat";
                break;
            case 47:
                *out_text = "Droknar's Forge";
                break;
            case 48:
                *out_text = "Druid's Overlook";
                break;
            case 49:
                *out_text = "Dunes of Despair";
                break;
            case 50:
                *out_text = "Durheim Archives";
                break;
            case 51:
                *out_text = "Dzagonur Bastion";
                break;
            case 52:
                *out_text = "Elona Reach";
                break;
            case 53:
                *out_text = "Embark Beach";
                break;
            case 54:
                *out_text = "Ember Light Camp";
                break;
            case 55:
                *out_text = "Eredon Terrace";
                break;
            case 56:
                *out_text = "Eternal Grove, The";
                break;
            case 57:
                *out_text = "Eye of the North";
                break;
            case 58:
                *out_text = "Fishermen's Haven";
                break;
            case 59:
                *out_text = "Fort Aspenwood (Kurzick)";
                break;
            case 60:
                *out_text = "Fort Aspenwood (Luxon)";
                break;
            case 61:
                *out_text = "Fort Ranik";
                break;
            case 62:
                *out_text = "Frontier Gate";
                break;
            case 63:
                *out_text = "Frost Gate, The";
                break;
            case 64:
                *out_text = "Gadd's Encampment";
                break;
            case 65:
                *out_text = "Gate of Anguish";
                break;
            case 66:
                *out_text = "Gate of Desolation";
                break;
            case 67:
                *out_text = "Gate of Fear";
                break;
            case 68:
                *out_text = "Gate of Madness";
                break;
            case 69:
                *out_text = "Gate of Pain";
                break;
            case 70:
                *out_text = "Gate of Secrets";
                break;
            case 71:
                *out_text = "Gate of the Nightfallen Lands";
                break;
            case 72:
                *out_text = "Gate of Torment";
                break;
            case 73:
                *out_text = "Gates of Kryta";
                break;
            case 74:
                *out_text = "Grand Court of Sebelkeh";
                break;
            case 75:
                *out_text = "Granite Citadel, The";
                break;
            case 76:
                *out_text = "Great Northern Wall, The";
                break;
            case 77:
                *out_text = "Great Temple of Balthazar";
                break;
            case 78:
                *out_text = "Grendich Courthouse";
                break;
            case 79:
                *out_text = "Gunnar's Hold";
                break;
            case 80:
                *out_text = "Gyala Hatchery";
                break;
            case 81:
                *out_text = "Harvest Temple";
                break;
            case 82:
                *out_text = "Hell's Precipice";
                break;
            case 83:
                *out_text = "Henge of Denravi";
                break;
            case 84:
                *out_text = "Heroes' Ascent";
                break;
            case 85:
                *out_text = "Heroes' Audience";
                break;
            case 86:
                *out_text = "Honur Hill";
                break;
            case 87:
                *out_text = "House zu Heltzer";
                break;
            case 88:
                *out_text = "Ice Caves of Sorrow";
                break;
            case 89:
                *out_text = "Ice Tooth Cave";
                break;
            case 90:
                *out_text = "Imperial Sanctum";
                break;
            case 91:
                *out_text = "Iron Mines of Moladune";
                break;
            case 92:
                *out_text = "Jade Flats (Kurzick)";
                break;
            case 93:
                *out_text = "Jade Flats (Luxon)";
                break;
            case 94:
                *out_text = "Jade Quarry (Kurzick), The";
                break;
            case 95:
                *out_text = "Jade Quarry (Luxon), The";
                break;
            case 96:
                *out_text = "Jennur's Horde";
                break;
            case 97:
                *out_text = "Jokanur Diggings";
                break;
            case 98:
                *out_text = "Kaineng Center";
                break;
            case 99:
                *out_text = "Kamadan, Jewel of Istan";
                break;
            case 100:
                *out_text = "Kodash Bazaar, The";
                break;
            case 101:
                *out_text = "Kodlonu Hamlet";
                break;
            case 102:
                *out_text = "Kodonur Crossroads";
                break;
            case 103:
                *out_text = "Lair of the Forgotten";
                break;
            case 104:
                *out_text = "Leviathan Pits";
                break;
            case 105:
                *out_text = "Lion's Arch";
                break;
            case 106:
                *out_text = "Longeye's Ledge";
                break;
            case 107:
                *out_text = "Lutgardis Conservatory";
                break;
            case 108:
                *out_text = "Maatu Keep";
                break;
            case 109:
                *out_text = "Maguuma Stade";
                break;
            case 110:
                *out_text = "Marhan's Grotto";
                break;
            case 111:
                *out_text = "Marketplace, The";
                break;
            case 112:
                *out_text = "Mihanu Township";
                break;
            case 113:
                *out_text = "Minister Cho's Estate";
                break;
            case 114:
                *out_text = "Moddok Crevice";
                break;
            case 115:
                *out_text = "Mouth of Torment, The";
                break;
            case 116:
                *out_text = "Nahpui Quarter";
                break;
            case 117:
                *out_text = "Nolani Academy";
                break;
            case 118:
                *out_text = "Nundu Bay";
                break;
            case 119:
                *out_text = "Olafstead";
                break;
            case 120:
                *out_text = "Piken Square";
                break;
            case 121:
                *out_text = "Pogahn Passage";
                break;
            case 122:
                *out_text = "Port Sledge";
                break;
            case 123:
                *out_text = "Quarrel Falls";
                break;
            case 124:
                *out_text = "Raisu Palace";
                break;
            case 125:
                *out_text = "Ran Musu Gardens";
                break;
            case 126:
                *out_text = "Random Arenas";
                break;
            case 127:
                *out_text = "Rata Sum";
                break;
            case 128:
                *out_text = "Remains of Sahlahja";
                break;
            case 129:
                *out_text = "Rilohn Refuge";
                break;
            case 130:
                *out_text = "Ring of Fire";
                break;
            case 131:
                *out_text = "Riverside Province";
                break;
            case 132:
                *out_text = "Ruins of Morah";
                break;
            case 133:
                *out_text = "Ruins of Surmia";
                break;
            case 134:
                *out_text = "Saint Anjeka's Shrine";
                break;
            case 135:
                *out_text = "Sanctum Cay";
                break;
            case 136:
                *out_text = "Sardelac Sanitarium";
                break;
            case 137:
                *out_text = "Seafarer's Rest";
                break;
            case 138:
                *out_text = "Seeker's Passage";
                break;
            case 139:
                *out_text = "Seitung Harbor";
                break;
            case 140:
                *out_text = "Senji's Corner";
                break;
            case 141:
                *out_text = "Serenity Temple";
                break;
            case 142:
                *out_text = "Shadow Nexus, The";
                break;
            case 143:
                *out_text = "Shing Jea Arena";
                break;
            case 144:
                *out_text = "Shing Jea Monastery";
                break;
            case 145:
                *out_text = "Sifhalla";
                break;
            case 146:
                *out_text = "Sunjiang District";
                break;
            case 147:
                *out_text = "Sunspear Arena";
                break;
            case 148:
                *out_text = "Sunspear Great Hall";
                break;
            case 149:
                *out_text = "Sunspear Sanctuary";
                break;
            case 150:
                *out_text = "Tahnnakai Temple";
                break;
            case 151:
                *out_text = "Tanglewood Copse";
                break;
            case 152:
                *out_text = "Tarnished Haven";
                break;
            case 153:
                *out_text = "Temple of the Ages";
                break;
            case 154:
                *out_text = "Thirsty River";
                break;
            case 155:
                *out_text = "Thunderhead Keep";
                break;
            case 156:
                *out_text = "Tihark Orchard";
                break;
            case 157:
                *out_text = "Tomb of the Primeval Kings";
                break;
            case 158:
                *out_text = "Tsumei Village";
                break;
            case 159:
                *out_text = "Umbral Grotto";
                break;
            case 160:
                *out_text = "Unwaking Waters (Kurzick)";
                break;
            case 161:
                *out_text = "Unwaking Waters (Luxon)";
                break;
            case 162:
                *out_text = "Urgoz's Warren";
                break;
            case 163:
                *out_text = "Vasburg Armory";
                break;
            case 164:
                *out_text = "Venta Cemetery";
                break;
            case 165:
                *out_text = "Ventari's Refuge";
                break;
            case 166:
                *out_text = "Vizunah Square (Foreign)";
                break;
            case 167:
                *out_text = "Vizunah Square (Local)";
                break;
            case 168:
                *out_text = "Vlox's Falls";
                break;
            case 169:
                *out_text = "Wehhan Terraces";
                break;
            case 170:
                *out_text = "Wilds, The";
                break;
            case 171:
                *out_text = "Yahnur Market";
                break;
            case 172:
                *out_text = "Yak's Bend";
                break;
            case 173:
                *out_text = "Yohlon Haven";
                break;
            case 174:
                *out_text = "Zaishen Challenge";
                break;
            case 175:
                *out_text = "Zaishen Elite";
                break;
            case 176:
                *out_text = "Zaishen Menagerie";
                break;
            case 177:
                *out_text = "Zen Daijun";
                break;
            case 178:
                *out_text = "Zin Ku Corridor";
                break;
            case 179:
                *out_text = "Zos Shivros Channel";
                break;
            default:
                *out_text = "";
        }
        return true;
    }
    // Returns guild struct of current location. Returns null on fail or non-guild map.
    static GW::Guild *GetCurrentGH()
    {
        GW::AreaInfo *m = GW::Map::GetCurrentMapInfo();
        if (!m || m->type != GW::RegionType::RegionType_GuildHall)
            return nullptr;
        const GW::Array<GW::Guild *>& guilds = GW::GuildMgr::GetGuildArray();
        if (!guilds.valid())
            return nullptr;
        for (size_t i = 0; i < guilds.size(); i++) {
            if (!guilds[i])
                continue;
            return guilds[i];
        }
        return nullptr;
    }
    static GW::Guild *GetPlayerGH()
    {
        const GW::Array<GW::Guild *> &guilds = GW::GuildMgr::GetGuildArray();
        if (!guilds.valid())
            return nullptr;
        uint32_t guild_idx = GW::GuildMgr::GetPlayerGuildIndex();
        if (guild_idx >= guilds.size())
            return nullptr;
        return guilds[guild_idx];
    }
    static bool IsInGH()
    {
        GW::Guild *gh = GetCurrentGH();
        return gh && gh == GetPlayerGH();
    }
    static bool IsLuxon()
    {
        GW::GuildContext *c = GW::GuildMgr::GetGuildContext();
        return c && c->player_guild_index && c->guilds[c->player_guild_index]->faction;
    }
    static bool IsAlreadyInOutpost(GW::Constants::MapID outpost_id, GW::Constants::District _district, uint32_t _district_number = 0)
    {
        return GW::Map::GetInstanceType() == GW::Constants::InstanceType::Outpost 
            && GW::Map::GetMapID() == outpost_id
            && TravelWindow::RegionFromDistrict(_district) == GW::Map::GetRegion() 
            && TravelWindow::LanguageFromDistrict(_district) == GW::Map::GetLanguage() 
            && (!_district_number || _district_number == static_cast<uint32_t>(GW::Map::GetDistrict()));
    }
}

void TravelWindow::Initialize() {
    ToolboxWindow::Initialize();
    Resources::Instance().LoadTextureAsync(&button_texture, Resources::GetPath(L"img\\icons", L"airplane.png"), 
        RESOURCES_DOWNLOAD_URL L"icons/airplane.png");
    Resources::Instance().LoadTextureAsync(&scroll_texture, Resources::GetPath(L"img\\materials", L"Scroll_of_Resurrection.png"), IDB_Mat_ResScroll);
    district = GW::Constants::District::Current;
    district_number = 0;

    GW::Chat::CreateCommand(L"tp", &CmdTP);
    GW::Chat::CreateCommand(L"to", &CmdTP);
    GW::Chat::CreateCommand(L"travel", &CmdTP);
}
void TravelWindow::Terminate() {
    ToolboxWindow::Terminate();
    if (scroll_texture)
        scroll_texture->Release();
    scroll_texture = nullptr;
}

void TravelWindow::TravelButton(const char* text, int x_idx, GW::Constants::MapID mapid) {
    if (x_idx != 0) ImGui::SameLine(0, ImGui::GetStyle().ItemInnerSpacing.x);
    float w = (ImGui::GetWindowContentRegionWidth() - ImGui::GetStyle().ItemInnerSpacing.x) / 2;
    bool clicked = false;
    switch (mapid) {
        case GW::Constants::MapID::The_Deep:
        case GW::Constants::MapID::Urgozs_Warren:
            clicked |= ImGui::IconButton(text, (ImTextureID) scroll_texture, ImVec2(w, 0));
            break;
        default:
            clicked |= ImGui::Button(text, ImVec2(w, 0));
            break;
    }
    if (clicked) {
        Travel(mapid, district, district_number);
        if (close_on_travel) visible = false;
    }
}

void TravelWindow::Draw(IDirect3DDevice9* pDevice) {
    UNREFERENCED_PARAMETER(pDevice);
    if (!visible) return;

    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver, ImVec2(.5f, .5f));
    ImGui::SetNextWindowSize(ImVec2(300, 0), ImGuiCond_FirstUseEver);
    if (ImInPresearing()) {
        if (ImGui::Begin(Name(), GetVisiblePtr(), GetWinFlags())) {
            TravelButton("Ascalon City", 0, GW::Constants::MapID::Ascalon_City_pre_searing);
            TravelButton("Ashford Abbey", 1, GW::Constants::MapID::Ashford_Abbey_outpost);
            TravelButton("Foible's Fair", 0, GW::Constants::MapID::Foibles_Fair_outpost);
            TravelButton("Fort Ranik", 1, GW::Constants::MapID::Fort_Ranik_pre_Searing_outpost);
            TravelButton("The Barradin Estate", 0, GW::Constants::MapID::The_Barradin_Estate_outpost);
        }
        ImGui::End();
    } else {

        if (ImGui::Begin(Name(), GetVisiblePtr(), GetWinFlags())) {
            ImGui::PushItemWidth(-1.0f);
            static int travelto_index = -1;
            if (ImGui::MyCombo("travelto", "Travel To...", &travelto_index, outpost_name_array_getter, nullptr, N_OUTPOSTS)) {
                GW::Constants::MapID id = IndexToOutpostID(travelto_index);
                Travel(id, district, district_number);
                travelto_index = -1;
                if (close_on_travel) visible = false;
            }

            static int district_index = 0;
            static const char* const district_words[] = { "Current District",
                "International",
                "American",
                "American District 1",
                "Europe English",
                "Europe French",
                "Europe German",
                "Europe Italian",
                "Europe Spanish",
                "Europe Polish",
                "Europe Russian",
                "Asian Korean",
                "Asia Chinese",
                "Asia Japanese", };
            if (ImGui::Combo("###district", &district_index, district_words, N_DISTRICTS)) {
                district_number = 0;
                switch (district_index) {
                    case 0: district = GW::Constants::District::Current; break;
                    case 1: district = GW::Constants::District::International; break;
                    case 2: district = GW::Constants::District::American; break;
                    case 3: // American District 1
                        district = GW::Constants::District::American;
                        district_number = 1;
                        break;
                    case 4: district = GW::Constants::District::EuropeEnglish; break;
                    case 5: district = GW::Constants::District::EuropeFrench; break;
                    case 6: district = GW::Constants::District::EuropeGerman; break;
                    case 7: district = GW::Constants::District::EuropeItalian; break;
                    case 8: district = GW::Constants::District::EuropeSpanish; break;
                    case 9: district = GW::Constants::District::EuropePolish; break;
                    case 10: district = GW::Constants::District::EuropeRussian; break;
                    case 11: district = GW::Constants::District::AsiaKorean; break;
                    case 12: district = GW::Constants::District::AsiaChinese; break;
                    case 13: district = GW::Constants::District::AsiaJapanese; break;
                    default:
                        break;
                }
            }
            ImGui::PopItemWidth();

            TravelButton("ToA", 0, GW::Constants::MapID::Temple_of_the_Ages);
            TravelButton("DoA", 1, GW::Constants::MapID::Domain_of_Anguish);
            TravelButton("Kamadan", 0, GW::Constants::MapID::Kamadan_Jewel_of_Istan_outpost);
            TravelButton("Embark", 1, GW::Constants::MapID::Embark_Beach);
            TravelButton("Vlox's", 0, GW::Constants::MapID::Vloxs_Falls);
            TravelButton("Gadd's", 1, GW::Constants::MapID::Gadds_Encampment_outpost);
            TravelButton("Urgoz", 0, GW::Constants::MapID::Urgozs_Warren);
            TravelButton("Deep", 1, GW::Constants::MapID::The_Deep);

            for (int i = 0; i < fav_count; ++i) {
                ImGui::PushID(i);
                ImGui::PushItemWidth(-40.0f - ImGui::GetStyle().ItemInnerSpacing.x);
                ImGui::MyCombo("", "Select a favorite", &fav_index[static_cast<size_t>(i)], outpost_name_array_getter, nullptr, N_OUTPOSTS);
                ImGui::PopItemWidth();
                ImGui::SameLine(0, ImGui::GetStyle().ItemInnerSpacing.x);
                if (ImGui::Button("Go", ImVec2(40.0f, 0))) {
                    TravelFavorite(static_cast<size_t>(i));
                }
                ImGui::PopID();
            }
        }
        ImGui::End();
    }
}

void TravelWindow::Update(float delta) {
    UNREFERENCED_PARAMETER(delta);
    if (scroll_to_outpost_id != GW::Constants::MapID::None) {
        ScrollToOutpost(scroll_to_outpost_id); // We're in the process of scrolling to an outpost
    }
}

bool TravelWindow::IsWaitingForMapTravel() {
    return GW::GameContext::instance()->party != nullptr && (GW::GameContext::instance()->party->flag & 0x8) > 0;
}

void TravelWindow::ScrollToOutpost(GW::Constants::MapID outpost_id, GW::Constants::District _district, uint32_t _district_number) {
    if (!GW::Map::GetIsMapLoaded() || !GW::PartyMgr::GetIsPartyLoaded()) {
        map_travel_countdown_started = false;
        pending_map_travel = false;
        return; // Map loading, so we're no longer waiting for travel timer to start or finish.
    }
    if (IsWaitingForMapTravel()) {
        map_travel_countdown_started = true;
        return; // Currently in travel countdown. Wait until the countdown is complete or cancelled.
    }
    if (map_travel_countdown_started) {
        pending_map_travel = false;
        map_travel_countdown_started = false;
        scroll_to_outpost_id = GW::Constants::MapID::None;
        return; // We were waiting for countdown, but it was cancelled.
    }
    if (pending_map_travel) {
        return; // Checking too soon; still waiting for either a map travel or a countdown for it.
    }

    GW::Constants::MapID map_id = GW::Map::GetMapID();
    if (scroll_to_outpost_id == GW::Constants::MapID::None) {
        scroll_to_outpost_id = outpost_id;
        scroll_from_outpost_id = map_id;
    }
    if (scroll_to_outpost_id != outpost_id) return; // Already travelling to another outpost
    if (map_id == outpost_id) {
        scroll_to_outpost_id = GW::Constants::MapID::None;
        if (!IsAlreadyInOutpost(outpost_id, _district, _district_number))
            UITravel(outpost_id, _district, _district_number);
        return; // Already at this outpost. Called GW::Map::Travel just in case district is different.
    }

    uint32_t scroll_model_id = 0;
    bool is_ready_to_scroll = map_id == GW::Constants::MapID::Embark_Beach;
    switch (scroll_to_outpost_id) {
    case GW::Constants::MapID::The_Deep:
        scroll_model_id = 22279;
        is_ready_to_scroll |= map_id == GW::Constants::MapID::Cavalon_outpost;
        break;
    case GW::Constants::MapID::Urgozs_Warren:
        scroll_model_id = 3256;
        is_ready_to_scroll |= map_id == GW::Constants::MapID::House_zu_Heltzer_outpost;
        break;
    default:
        Log::Error("Invalid outpost for scrolling");
        return;
    }
    if (!is_ready_to_scroll && scroll_from_outpost_id != map_id) {
        scroll_to_outpost_id = GW::Constants::MapID::None;
        return; // Not in scrollable outpost, but we're not in the outpost we started from either - user has decided to travel somewhere else.
    }

    GW::Item* scroll_to_use = GW::Items::GetItemByModelId(
        scroll_model_id,
        static_cast<int>(GW::Constants::Bag::Backpack),
        static_cast<int>(GW::Constants::Bag::Storage_14));
    if (!scroll_to_use) {
        scroll_to_outpost_id = GW::Constants::MapID::None;
        Log::Error("No scroll found in inventory for travel");
        return; // No scroll found.
    }
    if (is_ready_to_scroll) {
        scroll_to_outpost_id = GW::Constants::MapID::None;
        GW::Items::UseItem(scroll_to_use);
        return; // Done.
    }
    pending_map_travel = Travel(GW::Constants::MapID::Embark_Beach, _district, _district_number);
    //GW::Map::Travel(GW::Constants::MapID::Embark_Beach, district, district_number); // Travel to embark.
}

bool TravelWindow::Travel(GW::Constants::MapID MapID, GW::Constants::District _district /*= 0*/, uint32_t _district_number) {
    if (!IsMapUnlocked(MapID)) {
        Log::Error("[Error] Your character does not have %s unlocked", GW::Constants::NAME_FROM_ID[(uint32_t)MapID]);
        return false;
    }
    if (IsAlreadyInOutpost(MapID, _district, _district_number)) {
        Log::Error("[Error] You are already in the outpost");
        return false;
    }
    switch (MapID) {
        case GW::Constants::MapID::The_Deep:
        case GW::Constants::MapID::Urgozs_Warren:
            ScrollToOutpost(MapID, _district, _district_number);
            break;
        default:
            UITravel(MapID, _district, _district_number);
            break;
    }
    return true;
    //return GW::Map::Travel(MapID, District, district_number);
}
bool TravelWindow::IsMapUnlocked(GW::Constants::MapID map_id) {
    GW::Array<uint32_t> unlocked_map = GW::GameContext::instance()->world->unlocked_map;
    uint32_t real_index = (uint32_t)map_id / 32;
    if (real_index >= unlocked_map.size())
        return false;
    uint32_t shift = (uint32_t)map_id % 32;
    uint32_t flag = 1u << shift;
    return (unlocked_map[real_index] & flag) != 0;
}
void TravelWindow::UITravel(GW::Constants::MapID MapID, GW::Constants::District _district /*= 0*/, uint32_t _district_number) {
    struct MapStruct {
        GW::Constants::MapID map_id;
        int region_id;
        int language_id;
        uint32_t district_number;
    };
    MapStruct* t = new MapStruct();
    t->map_id = MapID;
    t->district_number = _district_number;
    t->region_id = RegionFromDistrict(_district);
    t->language_id = LanguageFromDistrict(_district);

    GW::GameThread::Enqueue([t] {
        GW::UI::SendUIMessage(GW::UI::kTravel, t);
        delete t;
    });
}

int TravelWindow::RegionFromDistrict(GW::Constants::District _district) {
    switch (_district) {
    case GW::Constants::District::International: return GW::Constants::Region::International;
    case GW::Constants::District::American: return GW::Constants::Region::America;
    case GW::Constants::District::EuropeEnglish:
    case GW::Constants::District::EuropeFrench:
    case GW::Constants::District::EuropeGerman:
    case GW::Constants::District::EuropeItalian:
    case GW::Constants::District::EuropeSpanish:
    case GW::Constants::District::EuropePolish:
    case GW::Constants::District::EuropeRussian:
        return GW::Constants::Region::Europe;
    case GW::Constants::District::AsiaKorean: return GW::Constants::Region::Korea;
    case GW::Constants::District::AsiaChinese: return GW::Constants::Region::China;
    case GW::Constants::District::AsiaJapanese: return GW::Constants::Region::Japan;
    default:
        break;
    }
    return GW::Map::GetRegion();
}
int TravelWindow::LanguageFromDistrict(GW::Constants::District _district)
{
    switch (_district) {
    case GW::Constants::District::EuropeEnglish: return GW::Constants::EuropeLanguage::English;
    case GW::Constants::District::EuropeFrench: return GW::Constants::EuropeLanguage::French;
    case GW::Constants::District::EuropeGerman: return GW::Constants::EuropeLanguage::German;
    case GW::Constants::District::EuropeItalian: return GW::Constants::EuropeLanguage::Italian;
    case GW::Constants::District::EuropeSpanish: return GW::Constants::EuropeLanguage::Spanish;
    case GW::Constants::District::EuropePolish: return GW::Constants::EuropeLanguage::Polish;
    case GW::Constants::District::EuropeRussian: return GW::Constants::EuropeLanguage::Russian;
    case GW::Constants::District::AsiaKorean:
    case GW::Constants::District::AsiaChinese:
    case GW::Constants::District::AsiaJapanese:
    case GW::Constants::District::International:
    case GW::Constants::District::American:
        return 0;
    default:
        break;
    }
    return GW::Map::GetLanguage();
}

bool TravelWindow::TravelFavorite(unsigned int idx) {
    if (idx >= fav_index.size())    return false;
    Travel(IndexToOutpostID(fav_index[idx]), district, district_number);
    if (close_on_travel) visible = false;
    return true;
}

void TravelWindow::DrawSettingInternal() {
    ImGui::Checkbox("Close on travel", &close_on_travel);
    ImGui::ShowHelp("Will close the travel window when clicking on a travel destination");
    ImGui::PushItemWidth(100.0f);
    if (ImGui::InputInt("Number of favorites", &fav_count)) {
        if (fav_count < 0) fav_count = 0;
        if (fav_count > 100) fav_count = 100;
        fav_index.resize(static_cast<size_t>(fav_count), -1);
    }
    ImGui::PopItemWidth();
}

void TravelWindow::LoadSettings(CSimpleIni* ini) {
    ToolboxWindow::LoadSettings(ini);
    show_menubutton = ini->GetBoolValue(Name(), VAR_NAME(show_menubutton), true);

    fav_count = ini->GetLongValue(Name(), VAR_NAME(fav_count), 3);
    fav_index.resize(static_cast<size_t>(fav_count), -1);
    for (int i = 0; i < fav_count; ++i) {
        char key[32];
        snprintf(key, 32, "Fav%d", i);
        fav_index[static_cast<size_t>(i)] = ini->GetLongValue(Name(), key, -1);
    }
    close_on_travel = ini->GetBoolValue(Name(), VAR_NAME(close_on_travel), false);
}

void TravelWindow::SaveSettings(CSimpleIni* ini) {
    ToolboxWindow::SaveSettings(ini);
    ini->SetLongValue(Name(), VAR_NAME(fav_count), fav_count);
    for (int i = 0; i < fav_count; ++i) {
        size_t ui = static_cast<size_t>(i);
        char key[32];
        snprintf(key, 32, "Fav%d", i);
        ini->SetLongValue(Name(), key, fav_index[ui]);
    }
    ini->SetBoolValue(Name(), VAR_NAME(close_on_travel), close_on_travel);
}

GW::Constants::MapID TravelWindow::IndexToOutpostID(int index) {
    using namespace GW::Constants;
    switch (index) {
    case 0: return MapID::Abaddons_Gate;
    case 1: return MapID::Abaddons_Mouth;
    case 2: return MapID::Altrumm_Ruins;
    case 3: return MapID::Amatz_Basin;
    case 4: return MapID::The_Amnoon_Oasis_outpost;
    case 5: return MapID::Arborstone_outpost_mission;
    case 6: return MapID::Ascalon_City_outpost;
    case 7: return MapID::Aspenwood_Gate_Kurzick_outpost;
    case 8: return MapID::Aspenwood_Gate_Luxon_outpost;
    case 9: return MapID::The_Astralarium_outpost;
    case 10: return MapID::Augury_Rock_outpost;
    case 11: return MapID::The_Aurios_Mines;
    case 12: return MapID::Aurora_Glade;
    case 13: return MapID::Bai_Paasu_Reach_outpost;
    case 14: return MapID::Basalt_Grotto_outpost;
    case 15: return MapID::Beacons_Perch_outpost;
    case 16: return MapID::Beetletun_outpost;
    case 17: return MapID::Beknur_Harbor;
    case 18: return MapID::Bergen_Hot_Springs_outpost;
    case 19: return MapID::Blacktide_Den;
    case 20: return MapID::Bloodstone_Fen;
    case 21: return MapID::Bone_Palace_outpost;
    case 22: return MapID::Boreal_Station_outpost;
    case 23: return MapID::Boreas_Seabed_outpost_mission;
    case 24: return MapID::Borlis_Pass;
    case 25: return MapID::Brauer_Academy_outpost;
    case 26: return MapID::Breaker_Hollow_outpost;
    case 27: return MapID::Camp_Hojanu_outpost;
    case 28: return MapID::Camp_Rankor_outpost;
    case 29: return MapID::Cavalon_outpost;
    case 30: return MapID::Central_Transfer_Chamber_outpost;
    case 31: return MapID::Chahbek_Village;
    case 32: return MapID::Champions_Dawn_outpost;
    case 33: return MapID::Chantry_of_Secrets_outpost;
    case 34: return MapID::Codex_Arena_outpost;
    case 35: return MapID::Consulate_Docks;
    case 36: return MapID::Copperhammer_Mines_outpost;
    case 37: return MapID::DAlessio_Seaboard;
    case 38: return MapID::Dajkah_Inlet;
    case 39: return MapID::Dasha_Vestibule;
    case 40: return MapID::The_Deep;
    case 41: return MapID::Deldrimor_War_Camp_outpost;
    case 42: return MapID::Destinys_Gorge_outpost;
    case 43: return MapID::Divinity_Coast;
    case 44: return MapID::Doomlore_Shrine_outpost;
    case 45: return MapID::The_Dragons_Lair;
    case 46: return MapID::Dragons_Throat;
    case 47: return MapID::Droknars_Forge_outpost;
    case 48: return MapID::Druids_Overlook_outpost;
    case 49: return MapID::Dunes_of_Despair;
    case 50: return MapID::Durheim_Archives_outpost;
    case 51: return MapID::Dzagonur_Bastion;
    case 52: return MapID::Elona_Reach;
    case 53: return MapID::Embark_Beach;
    case 54: return MapID::Ember_Light_Camp_outpost;
    case 55: return MapID::Eredon_Terrace_outpost;
    case 56: return MapID::The_Eternal_Grove_outpost_mission;
    case 57: return MapID::Eye_of_the_North_outpost;
    case 58: return MapID::Fishermens_Haven_outpost;
    case 59: return MapID::Fort_Aspenwood_Kurzick_outpost;
    case 60: return MapID::Fort_Aspenwood_Luxon_outpost;
    case 61: return MapID::Fort_Ranik;
    case 62: return MapID::Frontier_Gate_outpost;
    case 63: return MapID::The_Frost_Gate;
    case 64: return MapID::Gadds_Encampment_outpost;
    case 65: return MapID::Domain_of_Anguish;
    case 66: return MapID::Gate_of_Desolation;
    case 67: return MapID::Gate_of_Fear_outpost;
    case 68: return MapID::Gate_of_Madness;
    case 69: return MapID::Gate_of_Pain;
    case 70: return MapID::Gate_of_Secrets_outpost;
    case 71: return MapID::Gate_of_the_Nightfallen_Lands_outpost;
    case 72: return MapID::Gate_of_Torment_outpost;
    case 73: return MapID::Gates_of_Kryta;
    case 74: return MapID::Grand_Court_of_Sebelkeh;
    case 75: return MapID::The_Granite_Citadel_outpost;
    case 76: return MapID::The_Great_Northern_Wall;
    case 77: return MapID::Great_Temple_of_Balthazar_outpost;
    case 78: return MapID::Grendich_Courthouse_outpost;
    case 79: return MapID::Gunnars_Hold_outpost;
    case 80: return MapID::Gyala_Hatchery_outpost_mission;
    case 81: return MapID::Harvest_Temple_outpost;
    case 82: return MapID::Hells_Precipice;
    case 83: return MapID::Henge_of_Denravi_outpost;
    case 84: return MapID::Heroes_Ascent_outpost;
    case 85: return MapID::Heroes_Audience_outpost;
    case 86: return MapID::Honur_Hill_outpost;
    case 87: return MapID::House_zu_Heltzer_outpost;
    case 88: return MapID::Ice_Caves_of_Sorrow;
    case 89: return MapID::Ice_Tooth_Cave_outpost;
    case 90: return MapID::Imperial_Sanctum_outpost_mission;
    case 91: return MapID::Iron_Mines_of_Moladune;
    case 92: return MapID::Jade_Flats_Kurzick_outpost;
    case 93: return MapID::Jade_Flats_Luxon_outpost;
    case 94: return MapID::The_Jade_Quarry_Kurzick_outpost;
    case 95: return MapID::The_Jade_Quarry_Luxon_outpost;
    case 96: return MapID::Jennurs_Horde;
    case 97: return MapID::Jokanur_Diggings;
    case 98: return MapID::Kaineng_Center_outpost;
    case 99: return MapID::Kamadan_Jewel_of_Istan_outpost;
    case 100: return MapID::The_Kodash_Bazaar_outpost;
    case 101: return MapID::Kodlonu_Hamlet_outpost;
    case 102: return MapID::Kodonur_Crossroads;
    case 103: return MapID::Lair_of_the_Forgotten_outpost;
    case 104: return MapID::Leviathan_Pits_outpost;
    case 105: return MapID::Lions_Arch_outpost;
    case 106: return MapID::Longeyes_Ledge_outpost;
    case 107: return MapID::Lutgardis_Conservatory_outpost;
    case 108: return MapID::Maatu_Keep_outpost;
    case 109: return MapID::Maguuma_Stade_outpost;
    case 110: return MapID::Marhans_Grotto_outpost;
    case 111: return MapID::The_Marketplace_outpost;
    case 112: return MapID::Mihanu_Township_outpost;
    case 113: return MapID::Minister_Chos_Estate_outpost_mission;
    case 114: return MapID::Moddok_Crevice;
    case 115: return MapID::The_Mouth_of_Torment_outpost;
    case 116: return MapID::Nahpui_Quarter_outpost_mission;
    case 117: return MapID::Nolani_Academy;
    case 118: return MapID::Nundu_Bay;
    case 119: return MapID::Olafstead_outpost;
    case 120: return MapID::Piken_Square_outpost;
    case 121: return MapID::Pogahn_Passage;
    case 122: return MapID::Port_Sledge_outpost;
    case 123: return MapID::Quarrel_Falls_outpost;
    case 124: return MapID::Raisu_Palace_outpost_mission;
    case 125: return MapID::Ran_Musu_Gardens_outpost;
    case 126: return MapID::Random_Arenas_outpost;
    case 127: return MapID::Rata_Sum_outpost;
    case 128: return MapID::Remains_of_Sahlahja;
    case 129: return MapID::Rilohn_Refuge;
    case 130: return MapID::Ring_of_Fire;
    case 131: return MapID::Riverside_Province;
    case 132: return MapID::Ruins_of_Morah;
    case 133: return MapID::Ruins_of_Surmia;
    case 134: return MapID::Saint_Anjekas_Shrine_outpost;
    case 135: return MapID::Sanctum_Cay;
    case 136: return MapID::Sardelac_Sanitarium_outpost;
    case 137: return MapID::Seafarers_Rest_outpost;
    case 138: return MapID::Seekers_Passage_outpost;
    case 139: return MapID::Seitung_Harbor_outpost;
    case 140: return MapID::Senjis_Corner_outpost;
    case 141: return MapID::Serenity_Temple_outpost;
    case 142: return MapID::The_Shadow_Nexus;
    case 143: return MapID::Shing_Jea_Arena;
    case 144: return MapID::Shing_Jea_Monastery_outpost;
    case 145: return MapID::Sifhalla_outpost;
    case 146: return MapID::Sunjiang_District_outpost_mission;
    case 147: return MapID::Sunspear_Arena;
    case 148: return MapID::Sunspear_Great_Hall_outpost;
    case 149: return MapID::Sunspear_Sanctuary_outpost;
    case 150: return MapID::Tahnnakai_Temple_outpost_mission;
    case 151: return MapID::Tanglewood_Copse_outpost;
    case 152: return MapID::Tarnished_Haven_outpost;
    case 153: return MapID::Temple_of_the_Ages;
    case 154: return MapID::Thirsty_River;
    case 155: return MapID::Thunderhead_Keep;
    case 156: return MapID::Tihark_Orchard;
    case 157: return MapID::Tomb_of_the_Primeval_Kings;
    case 158: return MapID::Tsumei_Village_outpost;
    case 159: return MapID::Umbral_Grotto_outpost;
    case 160: return MapID::Unwaking_Waters_Kurzick_outpost;
    case 161: return MapID::Unwaking_Waters_Luxon_outpost;
    case 162: return MapID::Urgozs_Warren;
    case 163: return MapID::Vasburg_Armory_outpost;
    case 164: return MapID::Venta_Cemetery;
    case 165: return MapID::Ventaris_Refuge_outpost;
    case 166: return MapID::Vizunah_Square_Foreign_Quarter_outpost;
    case 167: return MapID::Vizunah_Square_Local_Quarter_outpost;
    case 168: return MapID::Vloxs_Falls;
    case 169: return MapID::Wehhan_Terraces_outpost;
    case 170: return MapID::The_Wilds;
    case 171: return MapID::Yahnur_Market_outpost;
    case 172: return MapID::Yaks_Bend_outpost;
    case 173: return MapID::Yohlon_Haven_outpost;
    case 174: return MapID::Zaishen_Challenge_outpost;
    case 175: return MapID::Zaishen_Elite_outpost;
    case 176: return MapID::Zaishen_Menagerie_outpost;
    case 177: return MapID::Zen_Daijun_outpost_mission;
    case 178: return MapID::Zin_Ku_Corridor_outpost;
    case 179: return MapID::Zos_Shivros_Channel;
    default: return MapID::Great_Temple_of_Balthazar_outpost;
    }
}

void TravelWindow::CmdTP(const wchar_t *message, int argc, LPWSTR *argv)
{
    UNREFERENCED_PARAMETER(message);
    // zero argument error
    if (argc == 1) {
        Log::Error("[Error] Please provide an argument");
        return;
    }
    GW::Constants::MapID outpost = GW::Map::GetMapID();
    GW::Constants::District district = GW::Constants::District::Current;
    uint32_t district_number = 0;

    std::wstring argOutpost = GuiUtils::ToLower(argv[1]);
    std::wstring argDistrict = GuiUtils::ToLower(argv[argc - 1]);
    // Guild hall
    if (argOutpost == L"gh") {
        if (argc == 2) {
            // "/tp gh"
            if (IsInGH())
                GW::GuildMgr::LeaveGH();
            else
                GW::GuildMgr::TravelGH();
            return;
        }
        // "/tp gh lag" = travel to Guild Hall belonging to Zero Files Remaining [LaG]
        std::wstring argGuildTag = GuiUtils::ToLower(argv[2]);
        const GW::GuildArray& guilds = GW::GuildMgr::GetGuildArray();
        for (GW::Guild *guild : guilds) {
            if (guild && GuiUtils::ToLower(guild->tag) == argGuildTag) {
                GW::GuildMgr::TravelGH(guild->key);
                return;
            }
        }
        Log::Error("[Error] Did not recognize guild '%ls'", argv[2]);
        return;
    }
    TravelWindow &instance = Instance();
    if (argOutpost.size() > 2 && argOutpost.compare(0, 3, L"fav", 3) == 0) {
        std::wstring fav_s_num = argOutpost.substr(3, std::wstring::npos);
        if (fav_s_num.empty()) {
            instance.TravelFavorite(0);
            return;
        }
        uint32_t fav_num;
        if (GuiUtils::ParseUInt(fav_s_num.c_str(), &fav_num) && fav_num > 0) {
            instance.TravelFavorite(fav_num - 1);
            return;
        }
        Log::Error("[Error] Did not recognize favourite");
        return;
    }
    for (int i = 2; i < argc - 1; i++) {
        // Outpost name can be anything after "/tp" but before the district e.g. "/tp house zu heltzer ae1"
        argOutpost.append(L" ");
        argOutpost.append(GuiUtils::ToLower(argv[i]));
    }
    bool isValidDistrict = ParseDistrict(argDistrict, district, district_number);
    if (isValidDistrict && argc == 2) {
        // e.g. "/tp ae1"
        instance.Travel(outpost, district, district_number); // NOTE: ParseDistrict sets district and district_number vars by reference.
        return;
    }
    if (!isValidDistrict && argc > 2) {
        // e.g. "/tp house zu heltzer"
        argOutpost.append(L" ");
        argOutpost.append(argDistrict);
    }
    if (ParseOutpost(argOutpost, outpost, district, district_number)) {
        switch (outpost) {
            case GW::Constants::MapID::Vizunah_Square_Foreign_Quarter_outpost:
            case GW::Constants::MapID::Vizunah_Square_Local_Quarter_outpost:
                if (std::wstring(L"l").rfind(argv[argc - 1]) == 0) // - e.g. /tp viz local
                    outpost = GW::Constants::MapID::Vizunah_Square_Local_Quarter_outpost;
                else if (std::wstring(L"f").rfind(argv[argc - 1]) == 0)
                    outpost = GW::Constants::MapID::Vizunah_Square_Foreign_Quarter_outpost;
                break;
            case GW::Constants::MapID::Fort_Aspenwood_Luxon_outpost:
            case GW::Constants::MapID::Fort_Aspenwood_Kurzick_outpost:
                if (std::wstring(L"l").rfind(argv[argc - 1]) == 0) // - e.g. /tp fa lux
                    outpost = GW::Constants::MapID::Fort_Aspenwood_Luxon_outpost;
                else if (std::wstring(L"k").rfind(argv[argc - 1]) == 0)
                    outpost = GW::Constants::MapID::Fort_Aspenwood_Kurzick_outpost;
                else
                    outpost = IsLuxon() ? GW::Constants::MapID::Fort_Aspenwood_Luxon_outpost : GW::Constants::MapID::Fort_Aspenwood_Kurzick_outpost;
                break;
            case GW::Constants::MapID::The_Jade_Quarry_Kurzick_outpost:
            case GW::Constants::MapID::The_Jade_Quarry_Luxon_outpost:
                if (std::wstring(L"l").rfind(argv[argc - 1]) == 0) // - e.g. /tp jq lux
                    outpost = GW::Constants::MapID::The_Jade_Quarry_Luxon_outpost;
                else if (std::wstring(L"k").rfind(argv[argc - 1]) == 0)
                    outpost = GW::Constants::MapID::Fort_Aspenwood_Kurzick_outpost;
                else
                    outpost = IsLuxon() ? GW::Constants::MapID::The_Jade_Quarry_Luxon_outpost : GW::Constants::MapID::The_Jade_Quarry_Kurzick_outpost;
                break;
            default:
                break;
        }
        instance.Travel(outpost, district, district_number); // NOTE: ParseOutpost sets outpost, district and district_number vars by reference.
        return;
    }
    Log::Error("[Error] Did not recognize outpost '%ls'", argOutpost.c_str());
    return;
}
bool TravelWindow::ParseOutpost(const std::wstring &s, GW::Constants::MapID &outpost, GW::Constants::District &district, uint32_t &number)
{
    // @Cleanup:
    // Should we parse this number here?
    number = 0;
    // By Map ID e.g. "/tp 77" for house zu heltzer
    uint32_t map_id = 0;
    if (GuiUtils::ParseUInt(s.c_str(), &map_id))
        return outpost = (GW::Constants::MapID)map_id, true;

    TravelWindow &instance = Instance();

    // By full outpost name (without punctuation) e.g. "/tp GrEaT TemplE oF BalthaZAR"
    std::string compare = GuiUtils::ToLower(GuiUtils::RemovePunctuation(GuiUtils::WStringToString(s)));

    // Shortcut words e.g "/tp doa" for domain of anguish
    std::string first_word = compare.substr(0, compare.find(' '));
    const auto &shorthand_outpost = instance.shorthand_outpost_names.find(first_word);
    if (shorthand_outpost != instance.shorthand_outpost_names.end()) {
        const OutpostAlias &outpost_info = shorthand_outpost->second;
        outpost = outpost_info.map_id;
        if (outpost_info.district != GW::Constants::District::Current)
            district = outpost_info.district;
        return true;
    }

    // Remove "the " from front of entered string
    std::size_t found = compare.rfind("the ");
    if (found == 0)
        compare.replace(found, 4, "");

    // Helper function
    auto FindMatchingMap = [](const std::string &compare, const char **map_names, const GW::Constants::MapID *map_ids, size_t map_count) -> GW::Constants::MapID {
        std::string sanitized;
        unsigned int searchStringLength = compare.length();
        unsigned int bestMatchLength = 0;
        unsigned int thisMapLength = 0;
        GW::Constants::MapID bestMatchMapID = GW::Constants::MapID::None;
        for (size_t i = 0; i < map_count; i++) {
            sanitized = map_names[i]; // Remove punctuation, to lower case.
            thisMapLength = sanitized.length();
            if (searchStringLength > thisMapLength)
                continue; // String entered by user is longer than this outpost name.
            if (sanitized.rfind(compare) != 0)
                continue; // No match
            if (bestMatchLength < thisMapLength) {
                bestMatchLength = thisMapLength;
                bestMatchMapID = map_ids[i];
                if (searchStringLength == thisMapLength)
                    return bestMatchMapID; // Exact match, break.
            }
        }
        return bestMatchMapID;
    };
    GW::Constants::MapID best_match_map_id = GW::Constants::MapID::None;
    if (ImInPresearing()) {
        best_match_map_id = FindMatchingMap(compare, instance.presearing_map_names, instance.presearing_map_ids, _countof(instance.presearing_map_ids));
    } else {
        best_match_map_id = FindMatchingMap(compare, instance.searchable_map_names, instance.searchable_map_ids, _countof(instance.searchable_map_ids));
        if (best_match_map_id == GW::Constants::MapID::None)
            best_match_map_id = FindMatchingMap(compare, instance.searchable_dungeon_names, instance.dungeon_map_ids, _countof(instance.dungeon_map_ids));
    }

    if (best_match_map_id != GW::Constants::MapID::None)
        return outpost = best_match_map_id, true; // Exact match
    return false;
}
bool TravelWindow::ParseDistrict(const std::wstring &s, GW::Constants::District &district, uint32_t &number)
{
    district = GW::Constants::District::Current;
    number = 0;
    std::string compare = GuiUtils::ToLower(GuiUtils::RemovePunctuation(GuiUtils::WStringToString(s)));
    // Shortcut words e.g "/tp ae" for american english
    std::string first_word = compare.substr(0, compare.find(' '));

    TravelWindow &instance = Instance();
    const auto &shorthand_outpost = instance.shorthand_district_names.find(first_word);
    if (shorthand_outpost != instance.shorthand_district_names.end()) {
        const DistrictAlias &outpost_info = shorthand_outpost->second;
        district = outpost_info.district;
        number = outpost_info.district_number;
        return true;
    }
    return false;
}
