% Channel: Adds an Extended Typical Urban LTE Fading Channel and AWGN Noise
% as well as Impairements like Frequency Offset and Delay
% Inputs: UETx - NPRACH Transmission Signal
%         delay - Number of Sample Delays
%         RCFO - Residual Carrier Frequency Offset
%         IFO - Integer Frequency Offset
%
function UETx = Channel(UETx, cvArea, delay, RCFO, slotNum)
    txParams = NPRACH_Config(cvArea);

    % Extracting Required Parameters
    Fs   = txParams.Fs;
    BETA = txParams.BETA;

    SNR = 10 ^ (txParams.SNRdB / 10);

    % Channel Configuarations
    chcfg.DelayProfile = 'EPA';
    chcfg.NRxAnts = 2;
    chcfg.DopplerFreq = 1;
    chcfg.MIMOCorrelation = 'Low';
    chcfg.Seed = 1;
    chcfg.InitPhase = 'Random';
    chcfg.ModelType = 'GMEDS';
    chcfg.NTerms = 16;
    chcfg.NormalizeTxAnts = 'On';
    chcfg.NormalizePathGains = 'On';  
    chcfg.SamplingRate = Fs;
    chcfg.InitTime = txParams.chInitTime * slotNum;
    
    [UETx, INFO] = lteFadingChannel(chcfg, UETx);
% 
%     Adding Delay, RCFO and AWGN Noise to the Transmitted Signal resp.
    delay = delay - INFO.ChannelFilterDelay;
    UETx(:, 1) = [zeros(delay, 1); exp(1i * 2 * pi * RCFO * (0:length(UETx)-1-delay)') .* UETx(1:end-delay, 1)];
    UETx(:, 2) = [zeros(delay, 1); exp(1i * 2 * pi * RCFO * (0:length(UETx)-1-delay)') .* UETx(1:end-delay, 2)];
    UETx = UETx(:, 1) + UETx(:, 2);
    noise = (BETA / sqrt(2 * SNR)) * (randn(size(UETx)) + 1i * randn(size(UETx)));
    UETx = UETx + noise;
end