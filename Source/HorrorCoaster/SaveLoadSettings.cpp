// Fill out your copyright notice in the Description page of Project Settings.

#include "SaveLoadSettings.h"
#include "HorrorCoaster.h"
#include "Runtime/Core/Public/Misc/Paths.h"
#include "Runtime/Core/Public/HAL/PlatformFilemanager.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"

bool USaveLoadSettings::LoadSetting(FString SettingsSection, FString SettingsKey, FString& SettingsValue) {
	FString path = "Config.ini";
	FString content;
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (!PlatformFile.FileExists(*(FPaths::ProjectDir() + path))) 
		return false;
	
	FFileHelper::LoadFileToString(content, *(FPaths::ProjectDir() + path));
	TArray<FString> lines;
	int32 count = content.ParseIntoArrayLines(lines, true);
	int32 index = 0;
	while (index < count) {
		if (lines[index].StartsWith("#"))
			continue;
		if (lines[index].StartsWith("[") && lines[index].Contains(SettingsSection)) {
			index++;
			while (index < count) {
				if (lines[index].StartsWith("[")) {
					index--;
					break;
				}
				if (lines[index].Contains(SettingsKey)) {
					FString lside;
					lines[index].Split("=", &lside, &SettingsValue);
					SettingsValue = SettingsValue.Trim();
					return true;
				}
				index++;
			}
		}
		index++;
	}
	return false;
}

bool USaveLoadSettings::SaveSetting(FString SettingsSection, FString SettingsKey, FString SettingsValue) {
	FString path = "Config.ini";
	FString content;
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (PlatformFile.FileExists(*(FPaths::ProjectDir() + path)))
		FFileHelper::LoadFileToString(content, *(FPaths::ProjectDir() + path));
	else
		content = "";
	TArray<FString> lines;
	int32 count = content.ParseIntoArrayLines(lines, true);
	
	int32 index = 0;
	while (index < count) {
		if (lines[index].StartsWith("#"))
			continue;
		if (lines[index].StartsWith("[") && lines[index].Contains(SettingsSection)) {
			index++;
			while (index < count) {
				if (lines[index].StartsWith("[")) {
					index--;
					break;
				}
				if (lines[index].Contains(SettingsKey)) {
					FString temp = "";
					for (int i = 0; i < index; i++) {
						temp.Append(lines[i]);
						temp.AppendChar('\n');
					}
					temp.Append(SettingsKey);
					temp.Append("=");
					temp.Append(SettingsValue);
					temp.AppendChar('\n');
					for (int i = index + 1; i < count; i++) {
						temp.Append(lines[i]);
						temp.AppendChar('\n');
					}
					FFileHelper::SaveStringToFile(temp, *(FPaths::ProjectDir() + path));
					return true;
				}
				index++;
			}
			FString temp = "";
			for (int i = 0; i < index; i++) {
				temp.Append(lines[i]);
				temp.AppendChar('\n');
			}
			temp.Append(SettingsKey);
			temp.Append("=");
			temp.Append(SettingsValue);
			temp.AppendChar('\n');
			for (int i = index + 1; i < count; i++) {
				temp.Append(lines[i]);
				temp.AppendChar('\n');
			}
			FFileHelper::SaveStringToFile(temp, *(FPaths::ProjectDir() + path));
			return true;
		}
		index++;
	}
	content.AppendChar('[');
	content.Append(SettingsSection);
	content.Append("]\n");
	content.Append(SettingsKey);
	content.AppendChar('=');
	content.Append(SettingsValue);
	content.AppendChar('\n');
	FFileHelper::SaveStringToFile(content, *(FPaths::ProjectDir() + path));
	return true;
}

FKey USaveLoadSettings::ConvertStringToNormalKey(FName KeyString) {
	return FKey(FName(KeyString));
}
