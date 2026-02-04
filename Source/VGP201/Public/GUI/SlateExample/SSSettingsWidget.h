// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameHUD.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class VGP201_API SSSettingsWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSSettingsWidget)
	{}
	SLATE_ARGUMENT(TWeakObjectPtr<class AGameHUD>, GameHUD)
	SLATE_ARGUMENT(int, MyInt)
	SLATE_END_ARGS()

	TWeakObjectPtr<class AGameHUD> GameHUD;
	int MyInt;

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	FReply OnResumeClicked() const;
	FReply OnIntClicked() const;
	FReply OnQuitClicked() const;
	/*
		---------- Smart Pointer Cheat Sheet ----------

		Unique Pointers: uniquePtr<T> = uniquePtr<int> Score;
			-Sole owner of the object
			-Cannot be copied
			-Automatically deallocates memory when it goes out of scope

		Shared Pointers: SharedPtr<T> = SharedPtr<int> Score;
			-Multiple ownership of the same object
			-Can be copied, increasing reference count
			-Automatuically deallocates memory when it goes out of scope
			-Eg. UI widgets, game object shared across system

		Weak Pointers: WeakPtr<T> = WeakPtr<int> Score;
			-Non-owning reference to an object
			-Doesn't affect reference count
			-Prevents circular references
			-Temporary access to memory

		Soft Object Pointers: SoftObjectPtr<T> = SoftObjectPtr<StaticMesh> HugeLevel80GB;
			-Reference to an asset that may not be loaded in memory
			-Loads assests on demand
			-Eg. Useful for large assets or optional content
	
	
	*/
};
