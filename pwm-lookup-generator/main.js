//
// Generates a lookup table for the positive half of a sine wave,
// at the desired resolution and frequency
//

const pad = require('pad');
const splitArray = require('split-array');

const MICROSECONDS_PER_SECOND = 1000000;
const CONFIG = require('./config.json');

const periodInMicroseconds = (1 / CONFIG.frequencyInHz) * MICROSECONDS_PER_SECOND;
const f = x => Math.sin(2 * Math.PI * x);

//
// Function that formats an array into multiple comma-delimited lines
//
const formatArray = (array, lines, linePrefix) => {
  const itemsPerLine = array.length / lines;
  const lineChunks = splitArray(result, 25);
  
  formatLine = lineChunk => lineChunk.map(item => pad(4, item.toString())).join(',');
  return lineChunks.map(lineChunk => linePrefix + formatLine(lineChunk)).join(',\n');
};

const result = [];

//
// Generate the first half of the sine wave (the positive half)
//
for(let step = 0; step < (CONFIG.resolutionInSteps / 2); step++) {
  const time = (1 / CONFIG.resolutionInSteps) * step;
  const value = CONFIG.amplitude * f(time);
  
  result.push(Math.round(value));
}

console.log(`
const short FREQUENCY_HZ = ${CONFIG.frequencyInHz};
const short PWM_LOOKUP[] = {
${formatArray(result, 10, '    ')}
};
const int PWM_LOOKUP_LENGTH = ${result.length};
const int PWM_STEP_MICROSECONDS = ${MICROSECONDS_PER_SECOND} / (FREQUENCY_HZ * PWM_LOOKUP_LENGTH * 2);
`);


(((1/20*2)/2)*1000000)/250