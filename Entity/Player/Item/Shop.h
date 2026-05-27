#pragma once

class Character;

class Shop
{
public:
	//아이템 정보 출력, 아이템 선택 구매
	void ShowItems( ) const;
	void BuyItem(Character* player , int choice);

	//상점을 호출 인터페이스
	void OpenShop(Character* player);

};

