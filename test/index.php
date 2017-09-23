<?php
/** PHPMem test script */

/** Simple glow and incross triggerbot for CS:GO */

require __DIR__.'/../phpmem_polyfill.php';
require __DIR__.'/csgo.php';

$handle = PHPMem::GetProcessHandle('csgo.exe');
if (!$handle)
  die('csgo not running');

$dwClient = PHPMem::GetModuleBase($handle, 'client.dll');
if (!$dwClient)
  die('could not get address of client.dll');

$dwLocalPlayer = PHPMem::ReadProcessMemory($handle, $dwClient + hazedumper\signatures::dwLocalPlayer, DataType::TYPE_LONG);
$dwGlowObjectManager = PHPMem::ReadProcessMemory($handle, $dwClient + hazedumper\signatures::dwGlowObjectManager, DataType::TYPE_LONG);

while (true) {
  $iCrosshairId = PHPMem::ReadProcessMemory($handle, $dwLocalPlayer + hazedumper\netvars::m_iCrosshairId, DataType::TYPE_LONG);
  if ($iCrosshairId > 0) {
    $dwEnemy = PHPMem::ReadProcessMemory($handle, $dwClient + hazedumper\signatures::dwEntityList + (($iCrosshairId - 1) * 0x10), DataType::TYPE_LONG);
    $iEnemyHealth = PHPMem::ReadProcessMemory($handle, $dwEnemy + hazedumper\netvars::m_iHealth, DataType::TYPE_LONG);
    $iEnemyTeam = PHPMem::ReadProcessMemory($handle, $dwEnemy + hazedumper\netvars::m_iTeamNum, DataType::TYPE_LONG);

    $iLocalPlayerTeam = PHPMem::ReadProcessMemory($handle, $dwLocalPlayer + hazedumper\netvars::m_iTeamNum, DataType::TYPE_LONG);

    if (($iEnemyTeam == 2 || $iEnemyTeam == 3) && $iEnemyTeam != $iLocalPlayerTeam && $iEnemyHealth > 0)
      PHPMem::WriteProcessMemory($handle, $dwClient + hazedumper\signatures::dwForceAttack, 6, DataType::TYPE_LONG);
  }

  for ($i = 0; $i < 65; $i++) {
    $dwCurrentPlayer = PHPMem::ReadProcessMemory($handle, $dwClient + hazedumper\signatures::dwEntityList + ($i * 0x10), DataType::TYPE_LONG);
    $bDormant = PHPMem::ReadProcessMemory($handle, $dwCurrentPlayer + 0xE9/*m_bDormant*/, DataType::TYPE_BOOL);

  	if ($bDormant) continue;

    $iGlowIndex = PHPMem::ReadProcessMemory($handle, $dwCurrentPlayer + hazedumper\netvars::m_iGlowIndex, DataType::TYPE_LONG);
    $iTeamNum = PHPMem::ReadProcessMemory($handle, $dwCurrentPlayer + hazedumper\netvars::m_iTeamNum, DataType::TYPE_LONG);

  	if ($iTeamNum != 2 && $iTeamNum != 3) continue;

  	$b = $iTeamNum == 3 ? 255.0 : 0.0;
    PHPMem::WriteProcessMemory($handle, $dwGlowObjectManager + (($iGlowIndex * 0x38) + 0xC), $b, DataType::TYPE_FLOAT);

    $g = 0.0;
    PHPMem::WriteProcessMemory($handle, $dwGlowObjectManager + (($iGlowIndex * 0x38) + 0x8), $g, DataType::TYPE_FLOAT);

    $r = $iTeamNum == 2 ? 255.0 : 0.0;
    PHPMem::WriteProcessMemory($handle, $dwGlowObjectManager + (($iGlowIndex * 0x38) + 0x4), $r, DataType::TYPE_FLOAT);

    $alpha = 255.0;
    PHPMem::WriteProcessMemory($handle, $dwGlowObjectManager + (($iGlowIndex * 0x38) + 0x10), $alpha, DataType::TYPE_FLOAT);

    PHPMem::WriteProcessMemory($handle, $dwGlowObjectManager + (($iGlowIndex * 0x38) + 0x24), true, DataType::TYPE_BOOL);
  }

  usleep(1 * 1000);
}
