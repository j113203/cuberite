
#pragma once

#include "BlockEntityWithItems.h"
#include "../BrewingRecipes.h"
#include "../Root.h"




class cClientHandle;





// tolua_begin
class cBrewingstandEntity :
	public cBlockEntityWithItems
{
	typedef cBlockEntityWithItems super;

public:
	enum
	{
		bsLeftBottle        = 0,  // Left bottle slot number
		bsMiddleBottle      = 1,  // Middle bottle slot number
		bsRightBottle       = 2,  // Right bottle slot number
		bsIngredient        = 3,  // Top ingredient slot number

		ContentsWidth       = 4,
		ContentsHeight      = 1,
	};

	// tolua_end

	BLOCKENTITY_PROTODEF(cBrewingstandEntity)

	/** Constructor used for normal operation */
	cBrewingstandEntity(int a_BlockX, int a_BlockY, int a_BlockZ, BLOCKTYPE a_BlockType, NIBBLETYPE a_BlockMeta, cWorld * a_World);

	virtual ~cBrewingstandEntity();

	//  cBlockEntity overrides:
	virtual void SendTo(cClientHandle & a_Client) override;
	virtual bool Tick(std::chrono::milliseconds a_Dt, cChunk & a_Chunk) override;
	virtual bool UsedBy(cPlayer * a_Player) override;
	virtual void Destroy() override
	{
		m_IsDestroyed = true;
		super::Destroy();
	}

	// tolua_begin

	/** Returns the time until the current items finishes brewing, in ticks */
	short GetBrewingTimeLeft(void) const { return m_NeedBrewingTime - m_TimeBrewed; }

	/** Returns the time that the current items has been brewing, in ticks */
	short GetTimeBrewed(void) { return m_TimeBrewed; }

	/** Returns the item in the left bottle slot  */
	const cItem & GetLeftBottleSlot(void) const { return GetSlot(bsLeftBottle); }

	/** Returns the item in the middle bottle slot  */
	const cItem & GetMiddleBottleSlot(void) const { return GetSlot(bsMiddleBottle); }

	/** Returns the item in the right bottle slot  */
	const cItem & GetRightBottleSlot(void) const { return GetSlot(bsRightBottle); }

	/** Returns the item in the ingredient slot  */
	const cItem & GetIndgredientSlot(void) const { return GetSlot(bsIngredient); }

	/** Get the expected result item for the given slot number */
	const cItem & GetResultItem(int a_SlotNumber) { return m_Results[a_SlotNumber]; }

	/** Sets the item in the left bottle slot  */
	void SetLeftBottleSlot(const cItem & a_Item) { SetSlot(bsLeftBottle, a_Item); }

	/** Sets the item in the middle bottle slot  */
	void SetMiddleBottleSlot(const cItem & a_Item) { SetSlot(bsMiddleBottle, a_Item); }

	/** Sets the item in the right bottle slot  */
	void SetRightBottleSlot(const cItem & a_Item) { SetSlot(bsRightBottle, a_Item); }

	/** Sets the item in the ingredient slot  */
	void SetIngredientSlot(const cItem & a_Item) { SetSlot(bsIngredient, a_Item); }

	// tolua_end

	/** Sets the current brewing time. Will be called if the brewing stand gets loaded from the world. */
	void setTimeBrewed(short a_TimeBrewed);

	/** Starts the brewing proccess. Will be called if the brewing stand gets loaded from the world. */
	void ContinueBrewing(void);

	/** Gets the recipes. Will be called if the brewing stand gets loaded from the world. */
	void GetRecipes(void);
protected:

	/** Block meta of the block currently represented by this entity */
	NIBBLETYPE m_BlockMeta;

	/** Set to true when the brewing stand entity has been destroyed to prevent the block being set again */
	bool m_IsDestroyed;

	/** Set to true if the brewing stand is brewing an item */
	bool m_IsBrewing;

	/** Brewing time is 400 ticks */
	const short m_NeedBrewingTime = 400;

	/** Store the current brewing recipes */
	const cBrewingRecipes::cRecipe * m_CurrentBrewingRecipes[3] = {};

	/** Result items for the  bottle inputs */
	cItem m_Results[3] = {};

	/** Amount of ticks that the current item has been brewed */
	short m_TimeBrewed;

	/** Sends the specified progressbar value to all clients of the window */
	void BroadcastProgress(short a_ProgressbarID, short a_Value);

	// /** Broadcasts progressbar updates, if needed */
	void UpdateProgressBars(bool a_ForceUpdate = false);

	// cItemGrid::cListener overrides:
	virtual void OnSlotChanged(cItemGrid * a_ItemGrid, int a_SlotNum) override;

} ;  // tolua_export





