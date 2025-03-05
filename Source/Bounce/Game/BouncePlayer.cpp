// Fill out your copyright notice in the Description page of Project Settings.


#include "BouncePlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ABouncePlayer::ABouncePlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	RootComponent = Mesh;
	SpringArm->SetupAttachment(Mesh);
	Camera->SetupAttachment(SpringArm);

	Mesh->SetSimulatePhysics(true);
	Mesh->OnComponentHit.AddDynamic(this, &ABouncePlayer::OnHit);
}

// Called when the game starts or when spawned
void ABouncePlayer::BeginPlay()
{
	Super::BeginPlay();

	MoveForce *= Mesh->GetMass();
	JumpImpulse *= Mesh->GetMass();
}

// Called to bind functionality to input
void ABouncePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveRight", this, &ABouncePlayer::MoveRight);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ABouncePlayer::Jump);
}

void ABouncePlayer::MoveRight(float Value) 
{
	const FVector Right = Camera->GetRightVector() * MoveForce * Value;
	Mesh->AddForce(Right);
}

void ABouncePlayer::Jump() 
{
	if (JumpCount >= MaxJumpCount) { return; }

	Mesh->AddImpulse(FVector(0, 0, JumpImpulse));

	JumpCount++;
}

void ABouncePlayer::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit )
{
	if (Hit.Normal.Z > 0) 
	{
		JumpCount = 0;
	}
}