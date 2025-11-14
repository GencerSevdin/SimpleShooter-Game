// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void PullTrigger();
private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;
	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;
	UPROPERTY(EditAnywhere)
	USoundBase* MuzzleSound;
	UPROPERTY(EditAnywhere)
	USoundBase* ImpactSound;
	UPROPERTY(EditAnywhere)
	UParticleSystem* ImpactParticle;
	bool bAutoDestroy = true;
	FVector Scale = FVector(1);
	float MaxRange = 2000;
	FHitResult HitResult;
	UPROPERTY(EditAnywhere)
	float Damage = 10;
	AController* GetOwnerController() const;
	bool GunTrace(FHitResult& Hit, FVector& ShotDirection);
	UPROPERTY(EditAnywhere)
	int32 MagazineCount =3;
	UPROPERTY(EditAnywhere)
	int32 Ammo = 30;
};
