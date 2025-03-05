// Fill out your copyright notice in the Description page of Project Settings.


#include "BounceItemBase.h"

#include "Bounce/Game/BounceGameMode.h"
#include "Bounce/Game/BouncePlayer.h"

// Sets default values
ABounceItemBase::ABounceItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ABounceItemBase::OverlapBegin);

}

// Called when the game starts or when spawned
void ABounceItemBase::BeginPlay()
{
	Super::BeginPlay();
}

void ABounceItemBase::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ABouncePlayer>(OtherActor) != nullptr)
	{
		Collected();
	}
}

void ABounceItemBase::Collected_Implementation()
{
	ABounceGameMode* GameMode = Cast<ABounceGameMode>(GetWorld()->GetAuthGameMode());

	if (GameMode)
	{
		GameMode->ItemCollected();
	}
}

