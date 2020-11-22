// Fill out your copyright notice in the Description page of Project Settings.


#include "SM_Planet.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ASM_Planet::ASM_Planet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	PlanetSphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Planet Sphere"));
	PlanetSphere->SetupAttachment(RootComponent);

	AtmosphereSphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Atmosphere Sphere"));
	AtmosphereSphere->SetupAttachment(PlanetSphere);

	GravitySphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gravity Sphere"));
	GravitySphere->SetupAttachment(PlanetSphere);
}

// Called when the game starts or when spawned
void ASM_Planet::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASM_Planet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASM_Planet::PullOverlappingActorsToPlanet(UMeshComponent* SphereComponent, float Strength) const
{
	TArray<UPrimitiveComponent*> OverlappingComponents;
	SphereComponent->GetOverlappingComponents(OverlappingComponents);
	for (auto Component : OverlappingComponents)
	{
		if (Component && Component->IsSimulatingPhysics())
		{
			const float SphereRadius = SphereComponent->Bounds.GetSphere().W;
			Component->AddRadialForce(GetActorLocation(), SphereRadius, -Strength, ERadialImpulseFalloff::RIF_Constant, true);
		}
	}
}

