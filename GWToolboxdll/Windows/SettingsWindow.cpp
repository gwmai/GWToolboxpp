#include "stdafx.h"

#include <GWCA/Constants/Constants.h>
#include <GWCA/Managers/MapMgr.h>

#include <Defines.h>
#include <GuiUtils.h>
#include <GWToolbox.h>

#include <Modules/ChatCommands.h>
#include <Modules/GameSettings.h>
#include <Modules/Resources.h>
#include <Modules/ToolboxSettings.h>
#include <Modules/ToolboxTheme.h>
#include <Modules/Updater.h>
#include <Windows/MainWindow.h>
#include <Windows/SettingsWindow.h>

void SettingsWindow::Initialize() {
    ToolboxWindow::Initialize();
    Resources::Instance().LoadTextureAsync(&button_texture, Resources::GetPath(L"img/icons", L"settings.png"), IDB_Icon_Settings);
}

void SettingsWindow::LoadSettings(CSimpleIni* ini) {
    ToolboxWindow::LoadSettings(ini);
    hide_when_entering_explorable = ini->GetBoolValue(Name(), VAR_NAME(hide_when_entering_explorable), hide_when_entering_explorable);
}
void SettingsWindow::SaveSettings(CSimpleIni* ini) {
    ToolboxWindow::SaveSettings(ini);
    ini->SetBoolValue(Name(), VAR_NAME(hide_when_entering_explorable), hide_when_entering_explorable);
}

void SettingsWindow::Draw(IDirect3DDevice9* pDevice) {
    UNREFERENCED_PARAMETER(pDevice);
    static GW::Constants::InstanceType last_instance_type = GW::Constants::InstanceType::Loading;
    GW::Constants::InstanceType instance_type = GW::Map::GetInstanceType();

    if (instance_type != last_instance_type) {
        if (hide_when_entering_explorable && instance_type == GW::Constants::InstanceType::Explorable)
            visible = false;
        last_instance_type = instance_type;
    }

    if (!visible) return;
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver, ImVec2(.5f, .5f));
    ImGui::SetNextWindowSize(ImVec2(450, 600), ImGuiCond_FirstUseEver);
    if (ImGui::Begin(Name(), GetVisiblePtr(), GetWinFlags())) {
        drawn_settings.clear();
        ImColor sCol(102, 187, 238, 255);
        ImGui::PushTextWrapPos();
        ImGui::Text("GWToolbox++");
        ImGui::SameLine(0, 0);
        ImGui::TextColored(sCol, " v%s ", GWTOOLBOXDLL_VERSION);
        if (ImGui::IsItemHovered()) 
            ImGui::SetTooltip("Go to %s", GWTOOLBOX_WEBSITE);
        if(ImGui::IsItemClicked())
            ShellExecute(NULL, "open", GWTOOLBOX_WEBSITE, NULL, NULL, SW_SHOWNORMAL);
        if (GWTOOLBOXDLL_VERSION_BETA[0]) {
            ImGui::SameLine();
            ImGui::Text("- %s", GWTOOLBOXDLL_VERSION_BETA);
        } else {
            const std::string server_version = Updater::Instance().GetServerVersion();
            if (!server_version.empty()) {
                if (server_version.compare(GWTOOLBOXDLL_VERSION) == 0) {
                    ImGui::SameLine();
                    ImGui::Text("(Up to date)");
                } else {
                    ImGui::Text("Version %s is available!", server_version.c_str());
                }
            }
        }
#ifdef _DEBUG
            ImGui::SameLine();
            ImGui::Text("(Debug)");
#endif
        float w = (ImGui::GetWindowContentRegionWidth() - ImGui::GetStyle().ItemSpacing.x) / 2;
        if (ImGui::Button("Open Settings Folder", ImVec2(w, 0))) {
            CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
            ShellExecuteW(NULL, L"open", Resources::GetSettingsFolderPath().c_str(), NULL, NULL, SW_SHOWNORMAL);
        }
        ImGui::SameLine();
        if (ImGui::Button("Open GWToolbox++ Website", ImVec2(w, 0))) {
            CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
            ShellExecute(NULL, "open", GWTOOLBOX_WEBSITE, NULL, NULL, SW_SHOWNORMAL);
        }

        ToolboxSettings::Instance().DrawFreezeSetting();
        ImGui::SameLine();
        ImGui::Checkbox("Hide Settings when entering explorable area", &hide_when_entering_explorable);

        ImGui::Text("General:");
        if (ImGui::CollapsingHeader("Help")) {
            if (ImGui::TreeNode("General Interface")) {
                ImGui::Bullet(); ImGui::Text("Double-click on the title bar to collapse a window.");
                ImGui::Bullet(); ImGui::Text("Click and drag on the lower right corner to resize a window.");
                ImGui::Bullet(); ImGui::Text("Click and drag on any empty space to move a window.");
                ImGui::Bullet(); ImGui::Text("Mouse Wheel to scroll.");
                if (ImGui::GetIO().FontAllowUserScaling) {
                    ImGui::Bullet(); ImGui::Text("CTRL+Mouse Wheel to zoom window contents.");
                }
                ImGui::Bullet(); ImGui::Text("TAB or SHIFT+TAB to cycle through keyboard editable fields.");
                ImGui::Bullet(); ImGui::Text("CTRL+Click or Double Click on a slider or drag box to input text.");
                ImGui::Bullet(); ImGui::Text(
                    "While editing text:\n"
                    "- Hold SHIFT or use mouse to select text\n"
                    "- CTRL+Left/Right to word jump\n"
                    "- CTRL+A or double-click to select all\n"
                    "- CTRL+X,CTRL+C,CTRL+V clipboard\n"
                    "- CTRL+Z,CTRL+Y undo/redo\n"
                    "- ESCAPE to revert\n"
                    "- You can apply arithmetic operators +,*,/ on numerical values. Use +- to subtract.\n");
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Opening and closing windows")) {
                ImGui::Text("There are several ways to open and close toolbox windows and widgets:");
                ImGui::Bullet(); ImGui::Text("Buttons in the main window.");
                ImGui::Bullet(); ImGui::Text("Checkboxes in the Info window.");
                ImGui::Bullet(); ImGui::Text("Checkboxes on the right of each setting header below.");
                ImGui::Bullet(); ImGui::Text("Chat command '/hide <name>' to hide a window or widget.");
                ImGui::Bullet(); ImGui::Text("Chat command '/show <name>' to show a window or widget.");
                ImGui::Bullet(); ImGui::Text("Chat command '/tb <name>' to toggle a window or widget.");
                ImGui::Indent();
                ImGui::Text("In the commands above, <name> is the title of the window as shown in the title bar. For example, try '/hide settings' and '/show settings'.");
                ImGui::Text("Note: the names of the widgets without a visible title bar are the same as in the setting headers below.");
                ImGui::Unindent();
                ImGui::Bullet(); ImGui::Text("Send Chat hotkey to enter one of the commands above.");
                ImGui::TreePop();
            }
            for (unsigned i = 0; i < GWToolbox::Instance().GetModules().size(); ++i) {
                GWToolbox::Instance().GetModules()[i]->DrawHelp();
            }
        }

        DrawSettingsSection(ToolboxTheme::Instance().SettingsName());
        DrawSettingsSection(ToolboxSettings::Instance().SettingsName());

        const std::vector<ToolboxModule*>& optional_modules = ToolboxSettings::Instance().GetOptionalModules();
        for (unsigned i = 0; i < optional_modules.size(); ++i) {
            if (i == sep_windows) ImGui::Text("Windows:");
            if (i == sep_widgets) ImGui::Text("Widgets:");
            DrawSettingsSection(optional_modules[i]->SettingsName());
        }

        if (ImGui::Button("Save Now", ImVec2(w, 0))) {
            GWToolbox::Instance().SaveSettings();
        }
        if (ImGui::IsItemHovered()) ImGui::SetTooltip("Toolbox normally saves settings on exit.\nClick to save to disk now.");
        ImGui::SameLine();
        if (ImGui::Button("Load Now", ImVec2(w, 0))) {
            GWToolbox::Instance().OpenSettingsFile();
            GWToolbox::Instance().LoadModuleSettings();
        }
        if (ImGui::IsItemHovered()) ImGui::SetTooltip("Toolbox normally loads settings on launch.\nClick to re-load from disk now.");
        ImGui::PopTextWrapPos();
    }
    ImGui::End();
}
