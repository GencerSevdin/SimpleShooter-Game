// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Gun.h"
#include "SimpleShooterGameMode.h"
#include "Components/CapsuleComponent.h"
#include "Rendering/RenderCommandPipes.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	for (auto Element : Guns)
	{
		GuntypeInArray = GetWorld()->SpawnActor<AGun>(Element);
		GetMesh()->HideBoneByName(TEXT("weapon_R"), EPhysBodyOp::PBO_None);
		GuntypeInArray->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
		GuntypeInArray->SetOwner(this);
		GuntypeInArray->SetActorHiddenInGame(true);
		Weapon.Add(GuntypeInArray);
	}
	Health = MaxHealth;
	Weapon[SelectedIndex]->SetActorHiddenInGame(false);
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis(  TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AShooterCharacter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AShooterCharacter::LookRightRate);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction(TEXT("Fire"),EInputEvent::IE_Pressed,this,&AShooterCharacter::Fire);
	PlayerInputComponent->BindAction(TEXT("GunSelector"),EInputEvent::IE_Pressed,this,&AShooterCharacter::ActiveIndex);
	
}
void AShooterCharacter:: MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
	
}

void AShooterCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}
void AShooterCharacter::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}
void AShooterCharacter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
	
}

void AShooterCharacter::ActiveIndex()
{
	SelectedIndex = (SelectedIndex + 1) % Guns.Num();
	EquipGun(SelectedIndex);
	isChangingGun = true;
	if (isChangingGun) PlayAnimMontage(GunSelection);
	
}

void AShooterCharacter::EquipGun(int32 NewIndex)
{
	for (auto Gun : Weapon)
	{
		if (Gun)
		{
			Gun->SetActorHiddenInGame(true);
		}
	}
	if (Weapon.IsValidIndex(NewIndex)&& Weapon[NewIndex])
	{
		Weapon[NewIndex]->SetActorHiddenInGame(false);
	}
	
}


void AShooterCharacter::Fire()
{
	USkeletalMeshComponent* CharacterMesh = GetMesh();
	UAnimInstance* AnimInstance = CharacterMesh->GetAnimInstance();
	for (int i = 0; i < MagazineCount; i++)
	{
		for (int j = 0; j < AmmoCount; j++)
		{
			if (!AnimInstance->Montage_IsPlaying(GunSelection)) Weapon[SelectedIndex]->PullTrigger();
		}
	}
}

float AShooterCharacter::GetHealthPercent() const
{
	  return Health / MaxHealth;
	
}

float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) 
{
	float DamageToApply =  Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;
	
	UE_LOG(LogTemp, Warning, TEXT("Health left %f"), Health);
	if (IsDead())
	{
		ASimpleShooterGameMode* GameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameMode>();
		if (GameMode!= nullptr)
		{
			GameMode->PawnKiled(this);
		}
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
		
	}
	return DamageToApply;
}
bool AShooterCharacter::IsDead() const
{
	return Health <= 0;
}



































