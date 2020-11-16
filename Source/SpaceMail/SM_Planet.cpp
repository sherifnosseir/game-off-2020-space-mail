// Fill out your copyright notice in the Description page of Project Settings.


#include "SM_Planet.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ASM_Planet::ASM_Planet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	PlanetSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Planet Sphere"));
    RootComponent = PlanetSphere;  

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMesh->SetupAttachment(PlanetSphere);
	
	GravitySphere = CreateDefaultSubobject<USphereComponent>(TEXT("Gravity Sphere"));
	GravitySphere->SetSphereRadius(GravitationSphereSize);
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

	this->AttractOverlappingActors();
}

void ASM_Planet::AttractOverlappingActors()
{
	TArray<UPrimitiveComponent*> OverlappingComponents;
    GravitySphere->GetOverlappingComponents(OverlappingComponents);
    for (auto Component : OverlappingComponents) 
    {
    	if (Component && Component->IsSimulatingPhysics())
    	{
    		const float SphereRadius = GravitySphere->GetScaledSphereRadius();
    		const float Strength = -GravitationPullStrength;

    		Component->AddRadialForce(GetActorLocation(), SphereRadius, Strength, ERadialImpulseFalloff::RIF_Constant, true);
    	}
    }
}

void ASM_Planet::PullOverlappingActorsToPlanet(UMeshComponent* SphereComponent)
{
	TArray<UPrimitiveComponent*> OverlappingComponents;
	SphereComponent->GetOverlappingComponents(OverlappingComponents);
	for (auto Component : OverlappingComponents) 
	{
		if (Component && Component->IsSimulatingPhysics())
		{
			const float SphereRadius = GravitySphere->GetScaledSphereRadius();
			const float Strength = -GravitationPullStrength*10000;

			Component->AddRadialForce(GetActorLocation(), SphereRadius, Strength, ERadialImpulseFalloff::RIF_Constant, true);
		}
	}
}

