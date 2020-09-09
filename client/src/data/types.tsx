

export type ParsedDataFrame = Array<any>;
export type ParsedLowResDataFrame = [ParsedDataFrame, ParsedDataFrame, ParsedDataFrame];
export type RawDataFrame = ArrayBuffer;

export type DataLayout = Array<{group: string, name: string, type: string}>;
export type DataFormat = {
    version: number,
    frame_time_us: number,
    total_num_lods: number,
    lod_sample_interval: 4,
    layout: DataLayout,
}
export type DatalogInfo = DataFormat & {
    date: string,
    jsdate: Date,
    duration: number,
}
