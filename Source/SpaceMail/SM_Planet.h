// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "SM_Planet.generated.h"

class USphereComponent;
class UStatichMeshComponent;

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

	UPROPERTY(BlueprintReadWrite, Category="Config")
	float PlanetSize = 1000;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Physics")
	USphereComponent* GravitySphere;

	UPROPERTY(BlueprintReadWrite, Category="Component")
	USphereComponent* PlanetSphere;
	
	UPROPERTY(VisibleAnywhere, Category="Component")
	UStaticMeshComponent* StaticMesh;

	UFUNCTION(BlueprintCallable)
    void PullOverlappingActorsToPlanet(UMeshComponent* SphereComponent);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, Category="Physics")
	float GravitationPullStrength;

	UPROPERTY(BlueprintReadWrite, Category="Physics")
	float AtmospherePullStrength;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Physics")
	float GravitationSphereSize;

private:
	void AttractOverlappingActors();
};
