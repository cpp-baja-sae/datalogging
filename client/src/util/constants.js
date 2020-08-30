export const BUFFER_LENGTH = 2048;
export const CHANNELS_PER_ADC = 8;
export const NUM_ADCS = 4;
export const NUM_CHANNELS = NUM_ADCS * CHANNELS_PER_ADC;
export const BATCH_SIZE = NUM_CHANNELS * 2; // 2 bytes per value.
export const MAX_VALUE = 65535;

export const UNITS = [
  'Volts',
  'Degrees',
];
export const UNIT_ABBREVIATIONS = {
  'Volts': 'V',
  'Degrees': '\u00B0',
}

export const COLORS = [
  '#ff1744',
  '#ff3d00',
  '#ff9100',
  '#ffc400',
  '#c6ff00',
  '#00ff96',
  '#00e5ff',
  '#d500f9',
]