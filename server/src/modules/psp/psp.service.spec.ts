import { Test, TestingModule } from '@nestjs/testing';
import { PspService } from './psp.service';

describe('PspService', () => {
  let service: PspService;

  beforeEach(async () => {
    const module: TestingModule = await Test.createTestingModule({
      providers: [PspService],
    }).compile();

    service = module.get<PspService>(PspService);
  });

  it('should be defined', () => {
    expect(service).toBeDefined();
  });
});
