#pragma once

#include "Utils.h"
#include <stdint.h>

typedef struct player_info_struct
{
	uint64_t version;
	union
	{
		uint64_t xuid;
		struct
		{
			uint32_t xuidLow;
			uint32_t xuidHigh;
		};
	};
	char name[128];
	int userId;
	char guid[33];
	uint32_t friendsId;
	char friendsName[128];
	bool fakeplayer;
	bool hltv;
	int customfiles[4];
	unsigned char filesdownloaded;
	int entityIndex;
} player_info_struct;

class Engine
{
public:
	constexpr auto getLocalPlayer() noexcept
	{
		return callVirtualMethod<int>(this, 12);
	}

	constexpr auto isInGame() noexcept
	{
		return callVirtualMethod<bool>(this, 26);
	}

	constexpr auto getPlayerInfo(int entityIndex, const player_info_struct& playerInfo) noexcept
	{
		return callVirtualMethod<bool, int, const player_info_struct&>(this, 8, entityIndex, playerInfo);
	}

	constexpr auto getPlayerForUserId(int userId) noexcept
	{
		return callVirtualMethod<int, int>(this, 9, userId);
	}

	constexpr auto getMaxClients() noexcept
	{
		return callVirtualMethod<int>(this, 20);
	}

	using self_matrix = float[4][4];
	constexpr auto worldToScreenMatrix() noexcept
	{
		return callVirtualMethod<const self_matrix&>(this, 37);
	}
};