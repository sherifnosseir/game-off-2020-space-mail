// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "SM_Planet.generated.h"

class UStaticMeshComponent;

UCLASS()
class SPACEMAIL_API ASM_Planet : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASM_Planet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// The sphere where gravity starts affecting incoming actors
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Physics")
	UStaticMeshComponent* GravitySphere;

	// The planet atmosphere, once an object enters the atmosphere, it should not escape
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Component")
	UStaticMeshComponent* AtmosphereSphere;

	// The sphere for the planet
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Component")
	UStaticMeshComponent* PlanetSphere;

	UFUNCTION(BlueprintCallable)
    void PullOverlappingActorsToPlanet(UMeshComponent* SphereComponent, float Strength) const;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// The strength of the planet's gravity pull
	UPROPERTY(BlueprintReadWrite, Category="Physics")
	float GravitationPullStrength = 3000;
};
