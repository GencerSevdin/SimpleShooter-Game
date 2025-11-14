// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;
UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	AGun* GuntypeInArray;
	UPROPERTY(EditAnywhere, Blueprintable)
	TArray<TSubclassOf<AGun>> Guns;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		                     class AController* EventInstigator, AActor* DamageCauser) override;
	UFUNCTION(BlueprintPure, Category = "Shooter")
	bool IsDead() const;
	void Fire();
	UFUNCTION(BlueprintPure, Category = "Shooter")
	float GetHealthPercent() const;
	UPROPERTY(BlueprintReadOnly)
	bool isChangingGun = false;
private:
	void MoveForward(float AxisValue);
	void LookUp(float AxisValue);
	void LookUpRate(float AxisValue);
	void MoveRight(float AxisValue);
	void LookRightRate(float AxisValue);
	void ActiveIndex();
	int32 SelectedIndex = 0;
	UPROPERTY(EditAnywhere)
	UAnimMontage* GunSelection;
	
	//UPROPERTY(EditAnywhere)
	//TSubclassOf<AGun>WeaponClass;
	
	TArray<AGun*>Weapon;
	UPROPERTY(EditAnywhere)
	int32 AmmoCount = 30;
	UPROPERTY(EditAnywhere)
	int32 MagazineCount = 3;
	UPROPERTY(EditAnywhere)
	float RotationRate = 10.f;
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100;
	UPROPERTY(VisibleAnywhere)
	float Health ;
	void EquipGun(int32 NewIndex);
};
