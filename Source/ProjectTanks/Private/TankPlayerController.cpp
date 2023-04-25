// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"


// enhanced input system handling as explained by Lively Geek here: https://www.youtube.com/watch?v=4wWIjlkSj2w&t=894s

// Maps a key to the input context and the action
static void Mapkey(UInputMappingContext* context, UInputAction* action, FKey key, 
	bool bNegate = false, float Deadzone = 0.f, bool bSwizzle = false, EInputAxisSwizzle swizzleaxis = EInputAxisSwizzle::YXZ)
{
	FEnhancedActionKeyMapping& mapping = context->MapKey(action, key);
	UObject* outer = context->GetOuter();

	if (bNegate)
	{
		mapping.Modifiers.Add(NewObject<UInputModifierNegate>(outer));
	}

	if (bSwizzle)
	{
		UInputModifierSwizzleAxis* swizzler = NewObject<UInputModifierSwizzleAxis>(outer);
		swizzler->Order = swizzleaxis;
		mapping.Modifiers.Add(swizzler);
	}

	if (Deadzone)
	{
		UInputModifierDeadZone* deadzones = NewObject<UInputModifierDeadZone>(outer);
		deadzones->LowerThreshold = Deadzone;
		mapping.Modifiers.Add(deadzones);
	}
}


void ATankPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// using enhanced input system, hopefully the right way

	MoveAction = NewObject<UInputAction>(this);
	MoveAction->ValueType = EInputActionValueType::Axis2D;

	ShootAction = NewObject<UInputAction>(this);
	ShootAction->ValueType = EInputActionValueType::Boolean;

	PlaceMineAction = NewObject<UInputAction>(this);
	PlaceMineAction->ValueType = EInputActionValueType::Boolean;

	MouseAimAction = NewObject<UInputAction>(this);
	MouseAimAction->ValueType = EInputActionValueType::Axis2D;

	GamepadAimAction = NewObject<UInputAction>(this);
	GamepadAimAction->ValueType = EInputActionValueType::Axis2D;

	// ############# KEYBOARD #############

	KeyboardMappingContext = NewObject<UInputMappingContext>(this);

	// Movement
	Mapkey(KeyboardMappingContext, MoveAction, EKeys::D);
	Mapkey(KeyboardMappingContext, MoveAction, EKeys::A, true);
	Mapkey(KeyboardMappingContext, MoveAction, EKeys::W, false, 0, true);
	Mapkey(KeyboardMappingContext, MoveAction, EKeys::S, true, 0, true);
	// Shoot
	Mapkey(KeyboardMappingContext, ShootAction, EKeys::LeftMouseButton);
	// Place mine
	Mapkey(KeyboardMappingContext, PlaceMineAction, EKeys::E);
	// Mouse Aim
	Mapkey(KeyboardMappingContext, MouseAimAction, EKeys::Mouse2D);

	// ############# GAMEPAD ############

	GamepadMappingContext = NewObject<UInputMappingContext>(this);

	// Movement
	Mapkey(GamepadMappingContext, MoveAction, EKeys::Gamepad_Left2D, false, .5f);
	// Shoot
	Mapkey(GamepadMappingContext, ShootAction, EKeys::Gamepad_RightShoulder);
	// Place mine
	Mapkey(GamepadMappingContext, PlaceMineAction, EKeys::Gamepad_LeftShoulder);
	// Gamepad Aim
	Mapkey(GamepadMappingContext, GamepadAimAction, EKeys::Gamepad_Right2D, false, .9f);
}

