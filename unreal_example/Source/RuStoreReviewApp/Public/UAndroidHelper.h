// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UAndroidHelper.generated.h"

UCLASS(Blueprintable)
class RUSTOREREVIEWAPP_API UAndroidHelper : public UObject
{
    GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "Open deeplink")
	static void OpenDeeplink(FString url);
};
