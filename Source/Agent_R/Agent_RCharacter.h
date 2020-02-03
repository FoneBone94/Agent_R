// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Agent_RCharacter.generated.h"

UCLASS(config=Game)
class AAgent_RCharacter : public ACharacter
{
	GENERATED_BODY()
		
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AAgent_RCharacter();

	//Player's total health
	int PlayerHealth;

		/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	

	protected:
		virtual void BeginPlay();
		
		virtual void Tick(float DeltaTime) override;
			   
		virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser);
		
		/** Called for forwards/backward input */
	void MoveForward(float Value);

	/**called for fast forwards/backwards input */
	void SprintForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**called for fast side input */
	void SprintRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 	 */
	void TurnAtRate(float Rate);
	 /** called when a damaging object intersects with the player character */
public:
	
	float TimelineValue;
	//UTimelineComponent* MyTimeline;
	struct FTimerHandle MemberTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float FullHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float HealthPercentage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		bool redFlash;

	/** Get Health */
	UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealth();

	/** Get Health Text */
	UFUNCTION(BlueprintPure, Category = "Health")
		FText GetHealthIntText();

	/** Set Damage State */
	UFUNCTION()
		void SetDamageState();

	UFUNCTION(BlueprintCallable, Category = "Power")
		void UpdateHealth(float HealthChange);

	/** Play Flash */
	UFUNCTION(BlueprintPure, Category = "Health")
		bool PlayFlash();

	/** Damage Timer */
	UFUNCTION()
		void DamageTimer();
	protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	};

