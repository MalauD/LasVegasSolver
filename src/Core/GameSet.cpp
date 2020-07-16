#include "GameSet.hpp"

GameSet::GameSet(std::vector<Casino> Casinos , std::vector<DiceSet> PlayerDiceSets) : m_Casinos{Casinos}, m_PlayerDiceSets{PlayerDiceSets}
{
}

GameSet::GameSet(std::vector<Casino> Casinos , std::vector<DiceSet> PlayerDiceSets, PlayingOrder playingOrder) : m_Casinos{Casinos}, m_PlayerDiceSets{PlayerDiceSets}, m_PlayingOrder{playingOrder}
{
}

void GameSet::AddDiceTo(Dice dice)
{
	std::for_each(m_Casinos.begin(), m_Casinos.end(),
		[&dice](Casino& c){
			if(dice.GetValue() == c.GetCasinoSymbol()) c.AddDice(dice);
		});
}

int GameSet::EvaluateForColor(DiceColors color)
{
	return std::accumulate(m_Casinos.begin(), m_Casinos.end(), 0,
		[&color](int prev, const Casino& c) {
			return prev + c.GetGainByColor(color);
		});
}

const std::vector<Casino> GameSet::GetCasinos(){
    return m_Casinos;
}

const std::vector<DiceSet> GameSet::GetDiceSets(){
    return m_PlayerDiceSets;
}

Casino& GameSet::GetCasinoBy(unsigned short Symbol){
	auto it = std::find_if(m_Casinos.begin(), m_Casinos.end(),
		[&Symbol](const Casino& c) {
			return c.GetCasinoSymbol() == Symbol;
		});
	if(it != m_Casinos.end())
		return m_Casinos[std::distance(m_Casinos.begin(), it)];
	throw std::runtime_error("Casino not found");
}

DiceSet& GameSet::GetDiceSetBy(DiceColors color) {
	auto it = std::find_if(m_PlayerDiceSets.begin(), m_PlayerDiceSets.end(),
		[&color](const DiceSet& Ds) {
			return Ds.GetColorOfFirst() == color;
		});
	if(it != m_PlayerDiceSets.end())
		return m_PlayerDiceSets[std::distance(m_PlayerDiceSets.begin(), it)];
	throw std::runtime_error("Dice not found");
}

int GameSet::GetDicesCountBy(DiceColors color)
{
	auto it = std::find_if(m_PlayerDiceSets.begin(), m_PlayerDiceSets.end(),
		[&color](const DiceSet& Ds) {
			return Ds.GetColorOfFirst() == color;
		});
	if (it != m_PlayerDiceSets.end())
		return m_PlayerDiceSets[std::distance(m_PlayerDiceSets.begin(), it)].GetDicesCount();
	return 0;
}

void GameSet::PlayFor(DiceColors playingFor, unsigned int Symbol) {
	auto& CorrespondingDs = GetDiceSetBy(playingFor);
	
	auto DicesToAdd = CorrespondingDs.GetAndRemove(Symbol);
	auto& casinoForSymbol = GetCasinoBy(Symbol);
	std::for_each(DicesToAdd.begin(), DicesToAdd.end(), [&casinoForSymbol](const Dice& d){
		casinoForSymbol.AddDice(d);
	});
	m_PlayingOrder.Advance();
}
void GameSet::SetDiceSetOf(DiceColors diceColor, DiceSet newDiceSet) {
	std::for_each(m_PlayerDiceSets.begin(), m_PlayerDiceSets.end(), [&newDiceSet, &diceColor](DiceSet& ds){
		if(ds.GetColorOfFirst() == diceColor) ds = newDiceSet;
	});
}

PlayingOrder& GameSet::GetPlayingOrder() {
	return m_PlayingOrder;
}