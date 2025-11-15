import { Test, TestingModule } from '@nestjs/testing';
import { PspController } from './psp.controller';

describe('PspController', () => {
  let controller: PspController;

  beforeEach(async () => {
    const module: TestingModule = await Test.createTestingModule({
      controllers: [PspController],
    }).compile();

    controller = module.get<PspController>(PspController);
  });

  it('should be defined', () => {
    expect(controller).toBeDefined();
  });
});
