// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "FPSGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API AFPSGameMode : public AGameMode
{
	GENERATED_BODY()
	AFPSGameMode(const FObjectInitializer& ObjectInitializer);
	virtual void StartPlay() override;
	
	
};
