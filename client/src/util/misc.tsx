export function formatMetricValue(value: number, units: string): string {
    const suffixes = ['G', 'M', 'k', '', 'm', 'u', 'n'];
    let divisor = Math.pow(1000, 3);
    for (let suffix of suffixes) {
        if (divisor > value) {
            divisor /= 1000;
            continue;
        }
        return (value / divisor).toPrecision(3) + ' ' + suffix + units;
    }
    return 'value too small';
}

export function formatDate(date: Date): string {
    return `${date.getDate()}-${date.getMonth()}-${date.getFullYear()} ${date.getHours()}:${date.getMinutes().toString().padStart(2, '0')}`;
}
