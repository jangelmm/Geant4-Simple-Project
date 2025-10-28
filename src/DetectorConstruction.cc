#include "DetectorConstruction.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"

DetectorConstruction::DetectorConstruction() = default;
DetectorConstruction::~DetectorConstruction() = default;

G4VPhysicalVolume* DetectorConstruction::Construct() {
    auto* nist = G4NistManager::Instance();
    auto* air = nist->FindOrBuildMaterial("G4_AIR");
    auto* water = nist->FindOrBuildMaterial("G4_WATER");

    // Mundo
    G4double worldSize = 1.0 * m;
    auto* worldSolid = new G4Box("World", worldSize/2, worldSize/2, worldSize/2);
    auto* worldLV = new G4LogicalVolume(worldSolid, air, "World");
    auto* worldPV = new G4PVPlacement(nullptr, {}, worldLV, "World", nullptr, false, 0);

    // Blanco
    G4double targetSize = 10.0 * cm;
    auto* targetSolid = new G4Box("Target", targetSize/2, targetSize/2, targetSize/2);
    fLogicTarget = new G4LogicalVolume(targetSolid, water, "Target");
    new G4PVPlacement(nullptr, {}, fLogicTarget, "Target", worldLV, false, 0);

    return worldPV;
}