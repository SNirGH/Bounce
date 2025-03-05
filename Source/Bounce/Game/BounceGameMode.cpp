// Fill out your copyright notice in the Description page of Project Settings.


#include "BounceGameMode.h"

#include "BounceItemCounter.h"
#include "Kismet/GameplayStatics.h"
#include "Bounce/Item/BounceItemBase.h"

void ABounceGameMode::BeginPlay()
{
	TArray<AActor*> Items;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABounceItemBase::StaticClass(), Items);

	ItemsInLevel = Items.Num();

	if (GameWidgetClass)
	{
		GameWidget = Cast<UBounceItemCounter>(CreateWidget(GetWorld(), GameWidgetClass));

		if (GameWidget)
		{
			GameWidget->AddToViewport();
			UpdateItemText();
		}
	}
}

void ABounceGameMode::UpdateItemText()
{
	GameWidget->SetItemText(ItemsCollected, ItemsInLevel);
}

void ABounceGameMode::ItemCollected()
{
	ItemsCollected++;
	UpdateItemText();
}
