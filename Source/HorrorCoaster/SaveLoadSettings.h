// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Runtime/InputCore/Classes/InputCoreTypes.h"
#include "SaveLoadSettings.generated.h"

/**
 * 
 */
UCLASS()
class HORRORCOASTER_API USaveLoadSettings : public UBlueprintFunctionLibrary
{
	GENERATED_BODY() public:

		UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "LoadSettings"))
			static bool LoadSetting(FString SettingsSection, FString SettingsKey, FString& SettingsValue);

		UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "SaveSettings"))
			static bool SaveSetting(FString SettingsSection, FString SettingsKey, FString SettingsValue);

		UFUNCTION(BlueprintPure, Category = "Custom", meta = (Keywords = "ConvertStringToNormalKey"))
			static FKey ConvertStringToNormalKey(FName KeyString);

};
